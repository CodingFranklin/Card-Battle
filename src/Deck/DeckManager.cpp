#include <algorithm>
#include <iostream>
#include <random>

#include "../Card/Card.h"
#include "../Effect/DamageEffect.h"
#include "../Effect/DrawCardEffect.h"
#include "../Effect/GainArmorEffect.h"
#include "../Effect/GainEnergyEffect.h"
#include "../Effect/GainStatusEffect.h"
#include "../Entity/StatusEffect/PoisonStatus.h"
#include "../Entity/StatusEffect/StrengthStatus.h"
#include "../Entity/StatusEffect/VulnerableStatus.h"
#include "../Entity/StatusEffect/WeakStatus.h"
#include "../Entity/StatusEffect/DexterityStatus.h"
//
// Created by lll on 2026/5/28.
//
using namespace std;
#include "DeckManager.h"

DeckManager::DeckManager():
    mainDeck(vector<unique_ptr<Card>>()),
    drawPile(vector<unique_ptr<Card>>()),
    handCards(vector<unique_ptr<Card>>()),
    discardPile(vector<unique_ptr<Card>>())
{
    for (int i=0; i<5; i++) {
        auto card = make_unique<Card>("打击", "Deal 6 damage.", 1, CardType::Attack, TargetType::Enemy);
        card->addEffect(make_unique<DamageEffect>(6));
        addOneCardToMainDeck(std::move(card));
    }
    for (int i=0; i<5; i++) {
        auto card = make_unique<Card>("防御", "Gain 5 armor.", 1, CardType::Skill, TargetType::Self);
        card->addEffect(make_unique<GainArmorEffect>(5));
        addOneCardToMainDeck(std::move(card));
    }

    auto specialCard1 = make_unique<Card>("灵动步伐", "Gain 2 dexterity.", 2, CardType::Skill, TargetType::Self);
    specialCard1->addEffect(make_unique<GainStatusEffect>(std::make_unique<DexterityStatus>(2)));
    addOneCardToMainDeck(std::move(specialCard1));

    auto specialCard2 = make_unique<Card>("痛击", "Deal 8 damage, add 2 Vulnerable to target.", 2, CardType::Attack, TargetType::Enemy);
    specialCard2->addEffect(make_unique<DamageEffect>(8));
    specialCard2->addEffect(make_unique<GainStatusEffect>(std::make_unique<VulnerableStatus>(2)));
    addOneCardToMainDeck(std::move(specialCard2));

    auto specialCard3 = make_unique<Card>("中和", "Deal 3 damage, add 2 Weak to target.", 0, CardType::Attack, TargetType::Enemy);
    specialCard3->addEffect(make_unique<DamageEffect>(3));
    specialCard3->addEffect(make_unique<GainStatusEffect>(make_unique<WeakStatus>(2)));
    addOneCardToMainDeck(std::move(specialCard3));

    auto specialCard4 = make_unique<Card>("毒瓶", "Add 5 Point to target.", 1, CardType::Skill, TargetType::Enemy);
    specialCard4->addEffect(make_unique<GainStatusEffect>(make_unique<PoisonStatus>(5)));
    addOneCardToMainDeck(std::move(specialCard4));

    auto specialCard5 = make_unique<Card>("燃烧之刃", "Gain 2 Strength.", 1, CardType::Skill, TargetType::Self);
    specialCard5->addEffect(make_unique<GainStatusEffect>(make_unique<StrengthStatus>(2)));
    addOneCardToMainDeck(std::move(specialCard5));

    auto specialCard6 = make_unique<Card>("神之一手", "Draw 2 cards.", 0, CardType::Skill, TargetType::Self);
    specialCard6->addEffect(make_unique<DrawCardEffect>(2));
    addOneCardToMainDeck(std::move(specialCard6));

    auto specialCard7 = make_unique<Card>("生产制造", "Gain 2 energy.", 0, CardType::Skill, TargetType::Self);
    specialCard7->addEffect(make_unique<GainEnergyEffect>(2));
    addOneCardToMainDeck(std::move(specialCard7));

    resetDrawPileFromMainDeck();
}

/**
 * 将抽牌堆初始化，把所有主牌堆的牌克隆到抽牌堆并打乱
 */
void DeckManager::resetDrawPileFromMainDeck() {
    drawPile.clear();
    handCards.clear();
    discardPile.clear();

    for (const auto& card : mainDeck) {
        drawPile.push_back(card->clone());
    }

    shuffleDrawPile();
}

/**
 * 从抽牌堆抽qty数量的牌
 * @param qty 抽牌数量
 */
void DeckManager::drawCards(int qty) {
    // move qty number of cards from drawPile to handCards
    // !!! the remove order will start from the back !!!
    for (int i = 0; i < qty; i++) {
        if (handCards.size() >= 10) {
            cout << "You already have too many cards in your hand!" << endl;
            return;
        }
        // 若是抽牌过程中抽牌堆为空，则先将弃牌堆打乱洗入抽牌堆
        if (drawPile.empty()) {
            reshuffleDiscardPileIntoDrawPile();
        }

        if (drawPile.empty()) {
            cout << "No cards left to draw." << endl;
            return;
        }

        handCards.push_back(std::move(drawPile.back()));
        // delete the null pointer
        drawPile.pop_back();
    }
}

/**
 * 将手牌的第index张牌打出，然后放入弃牌堆
 * @param index 第几张牌
 * @param player 玩家对象
 * @param targets 多个或单个目标对象（vector）
 */
bool DeckManager::playHandCard(int index, Player& player, std::vector<Character*> targets) {
    if (index < 0 || index >= static_cast<int>(handCards.size())) {
        std::cout << "Invalid card index." << std::endl;
        return false;
    }

    bool played = handCards[index]->play(player, targets);

    if (!played) {
        return false;
    }

    discardHandCard(index, false);
    return true;
}

/**
 * (默认)当discardAll为false：则弃置第index张牌\n
 * 当discardAll为true：则弃置全部手牌
 * @param index 第几张牌
 * @param discardAll 是否弃置所有手牌
 */
void DeckManager::discardHandCard(int index, bool discardAll) {
    if (discardAll) {
        // move all hand cards to discardPile
        for (int i = 0; i < getHandCardsSize(); i++) {
            if (handCards[i].get() != nullptr) {
                discardPile.push_back(std::move(handCards[i]));
            }
        }
        // TODO 以后可能加上‘保留’机制
        handCards.clear();
        return;
    }
    if (index < 0 || index >= static_cast<int>(handCards.size())) {
        std::cout << "Invalid discard index." << std::endl;
        return;
    }
    // move the card in handCards with given index to discardPile
    discardPile.push_back(std::move(handCards[index]));
    handCards.erase(handCards.begin() + index);

}

/**
 * 将弃牌堆所有牌洗入抽牌堆，并打乱
 */
void DeckManager::reshuffleDiscardPileIntoDrawPile(){
    // move first
    while (!discardPile.empty()) {
        drawPile.push_back(std::move(discardPile.back()));
        discardPile.pop_back();
    }

    // then shuffle
    shuffleDrawPile();
}

/**
 * 打乱抽牌堆
 */
void DeckManager::shuffleDrawPile() {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(drawPile.begin(), drawPile.end(), rng);
}

/**
 *向主牌堆加入一张牌
 * @param card unique_ptr<Card>
 */
void DeckManager::addOneCardToMainDeck(unique_ptr<Card> card) {
    mainDeck.push_back(std::move(card));
}

/**
 * 将手牌打印出来在terminal中
 */
void DeckManager::printHandCards() const {
    if (handCards.empty()) {
        cout << "Hand is empty." << endl;
        return;
    }

    cout << "===== Hand Cards =====" << endl;

    for (int i = 0; i < getHandCardsSize(); i++) {
        cout << i + 1 << ". "
                  << handCards[i]->getName()
                  << " | Cost: "
                  << handCards[i]->getCost()
                  << endl;
    }

    std::cout << "======================" << std::endl;
}

int DeckManager::getHandCardsSize() const { return handCards.size(); }
int DeckManager::getDrawPileSize() const { return drawPile.size(); }

Card* DeckManager::getHandCard(int index) const {
    if (index < 0 || index >= static_cast<int>(handCards.size())) {
        std::cout << "Hand card index out of bounds." << std::endl;
        return nullptr;
    }
    return handCards[index].get();
}
