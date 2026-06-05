//
// Created by lll on 2026/5/27.
//
#include "random"

#include "Battle.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ostream>

#include "../Card/Card.h"


Battle::Battle(Player& player, std::vector<Enemy*>& enemies)
    : player(player), enemies(enemies), turnManager(), battleOver(false)
{
    bindEvents();
}

void Battle::start() {
    std::cout << "Battle Start!" << std::endl;

    while (!battleOver) {
        runPlayerTurn();

        if (battleOver) {
            break;
        }

        runEnemyTurn();
    }

    std::cout << "Battle End!" << std::endl;
}

void Battle::runPlayerTurn() {
    turnManager.startPlayerTurn();

    while (player.getEnergy() > 0 && !battleOver) {
        playerAct();
        checkBattleEnd();
        printBattleStatus();
    }

    if (!battleOver) {
        turnManager.endPlayerTurn();
    }
}

void Battle::runEnemyTurn() {
    turnManager.startEnemyTurn();

    enemyAct();

    checkBattleEnd();

    if (!battleOver) {
        turnManager.endEnemyTurn();
    }
}

void Battle::playerAct() {
    //  多牌选择
    player.deckManager.printHandCards();
    std::cout << "Choose a card index: ";
    int cardIndex;
    std::cin >> cardIndex;
    // 输入0表示主动将回合结束
    if (cardIndex == 0) {
        player.gainEnergy(-player.getEnergy());
        return;
    }
    int playIndex = cardIndex - 1;

    Card* card = player.deckManager.getHandCard(playIndex);
    if (card == nullptr) {
        std::cout << "Invalid card index." << std::endl;
        return;
    }

    std::vector<Character*> targets = resolveTargets(card);

    player.deckManager.playHandCard(playIndex, player, targets);
}

std::vector<Character *> Battle::resolveTargets(Card *card) {
    std::vector<Character*> targets = {};
    TargetType targetType = card->getTargetType();

    switch (targetType) {
        case TargetType::Enemy: {
            Character* target = chooseEnemyTarget();
            if (target == nullptr) return targets;
            targets.push_back(target);
            break;
        }
        case TargetType::Self: {
            targets.push_back(&player);
            break;
        }
        case TargetType::AllEnemies: {
            for (Enemy* enemy : enemies) {
                if (enemy != nullptr && !enemy->isDead()) {
                    targets.push_back(enemy);
                }
            }
            break;
        }
        case TargetType::None: {
            break;
        }
    }

    return targets;
}

void Battle::enemyAct() {
    for (Enemy* enemy : enemies) {
        if (!enemy->isDead()) {
            std::cout << enemy->getName() << " attacks player" << std::endl;
            enemy->dealDamageTo(player, enemy->getDamage());
        }
    }

    std::cout << "Player HP: "
              << player.getCurHealth()
              << "/"
              << player.getMaxHealth()
              << std::endl;
}

/*
 * ========= 所有有关回合内发生的事件在此添加修改 =========
 */
void Battle::bindEvents() {
    turnManager.onPlayerTurnStart.addListener([this]() {
        player.beginTurn();
        printBattleStatus();
        // 回合开始抽5张牌
        // 若抽牌堆为空则先将弃牌堆所有牌打乱洗入抽牌堆
        if (player.deckManager.getDrawPileSize() == 0) {
            player.deckManager.reshuffleDiscardPileIntoDrawPile();
        }
        player.deckManager.drawCards(5);
    });

    turnManager.onPlayerTurnEnd.addListener([this]() {
        player.endTurn();
        // 回合结束弃掉所有手牌
        player.deckManager.discardHandCard(0, true);
    });

    turnManager.onEnemyTurnStart.addListener([this]() {
        for (Enemy* enemy : enemies) {
            if (!enemy->isDead()) {
                enemy->beginTurn();
            }
        }
    });

    turnManager.onEnemyTurnEnd.addListener([this]() {
        for (Enemy* enemy : enemies) {
            if (!enemy->isDead()) {
                enemy->endTurn();
            }
        }
    });
}

void Battle::checkBattleEnd() {
    if (player.isDead()) {
        std::cout << "Player lost!" << std::endl;
        battleOver = true;
        return;
    }

    bool allEnemiesDead = true;

    for (Enemy* enemy : enemies) {
        if (!enemy->isDead()) {
            allEnemiesDead = false;
            break;
        }
    }

    if (allEnemiesDead) {
        std::cout << "Battle won!" << std::endl;
        battleOver = true;
    }
}

Enemy* Battle::chooseEnemyTarget() {
    std::vector<Enemy*> aliveEnemies;

    for (Enemy* enemy : enemies) {
        if (enemy != nullptr && !enemy->isDead()) {
            aliveEnemies.push_back(enemy);
        }
    }

    if (aliveEnemies.empty()) {
        return nullptr;
    }

    std::cout << "Choose an enemy target:" << std::endl;

    for (int i = 0; i < static_cast<int>(aliveEnemies.size()); i++) {
        std::cout << i + 1 << ". "
                  << aliveEnemies[i]->getName()
                  << " HP: "
                  << aliveEnemies[i]->getCurHealth()
                  << "/"
                  << aliveEnemies[i]->getMaxHealth()
                  << std::endl;
    }

    int choice;
    std::cin >> choice;

    int enemyIndex = choice - 1;

    if (enemyIndex < 0 || enemyIndex >= static_cast<int>(aliveEnemies.size())) {
        std::cout << "Invalid choice!" << std::endl;
        return nullptr;
    }

    return aliveEnemies[enemyIndex];
}


void Battle::printBattleStatus() const {
    std::cout << "\n========== Battle Status ==========" << std::endl;

    // ================= Player =================
    std::cout << "\n[Player]" << std::endl;

    std::string playerHealth =
        std::to_string(static_cast<int>(player.getCurHealth())) +
        "/" +
        std::to_string(static_cast<int>(player.getMaxHealth()));

    std::string playerEnergy =
        std::to_string(player.getEnergy()) +
        "/" +
        std::to_string(player.getMaxEnergy());

    std::cout << std::left
              << std::setw(15) << "Name"
              << std::setw(15) << "Health"
              << std::setw(15) << "Armor"
              << std::setw(15) << "Energy"
              << std::endl;

    std::cout << std::left
              << std::setw(15) << player.getName()
              << std::setw(15) << playerHealth
              << std::setw(15) << player.getArmor()
              << std::setw(15) << playerEnergy
              << std::endl;

    std::cout << "状态：" << player.getStatusText() << std::endl;


    // ================= Enemies =================
    std::cout << "\n[Enemies]" << std::endl;

    for (int i = 0; i < static_cast<int>(enemies.size()); i++) {
        Enemy* enemy = enemies[i];

        if (enemy == nullptr) {
            continue;
        }

        std::string enemyHealth =
            std::to_string(static_cast<int>(enemy->getCurHealth())) +
            "/" +
            std::to_string(static_cast<int>(enemy->getMaxHealth()));

        std::cout << "\nEnemy " << i + 1 << std::endl;

        std::cout << std::left
                  << std::setw(15) << "Name"
                  << std::setw(15) << "Health"
                  << std::setw(15) << "Armor"
                  << std::endl;

        std::cout << std::left
                  << std::setw(15) << enemy->getName()
                  << std::setw(15) << enemyHealth
                  << std::setw(15) << enemy->getArmor()
                  << std::endl;

        std::cout << "状态：" << enemy->getStatusText() << std::endl;
    }

    std::cout << "===================================\n" << std::endl;
}