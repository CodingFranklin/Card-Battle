#include <algorithm>
#include <iostream>
#include <random>

#include "DeckManager.h"
#include "DeckLoader.h"

using namespace std;

DeckManager::DeckManager():
    mainDeck(vector<unique_ptr<Card>>()),
    drawPile(vector<unique_ptr<Card>>()),
    handCards(vector<unique_ptr<Card>>()),
    discardPile(vector<unique_ptr<Card>>())
{}

bool DeckManager::initializeFromJson(const std::string& cardsFilePath, const std::string& starterDeckFilePath) {
    mainDeck.clear();
    drawPile.clear();
    handCards.clear();
    discardPile.clear();

    return DeckLoader::loadMainDeckFromJson(*this, cardsFilePath, starterDeckFilePath);
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
 * @param target 目标对象
 */
bool DeckManager::playHandCard(int index, ActionContext& context) {
    if (index < 0 || index >= static_cast<int>(handCards.size())) {
        std::cout << "Invalid card index." << std::endl;
        return false;
    }

    bool played = handCards[index]->play(context);

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
