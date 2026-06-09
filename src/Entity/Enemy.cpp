//
// Created by lll on 2026/5/26.
//

#include "Enemy.h"

#include <iostream>

Enemy::Enemy(
    const std::string& name,
    int maxHealth,
    int damage
)
    : Character(name, maxHealth),
      damage(damage) {
}

void Enemy::doAction(ActionContext& context) {
    if (actionList.empty()) {
        return;
    }

    std::cout << "[DEBUG] " << getName()
              << " executing: "
              << actionList[nextActionIndex].getName()
              << '\n';

    actionList[nextActionIndex].act(context);

    // 自动循环
    nextActionIndex =
        (nextActionIndex + 1) % actionList.size();
}

void Enemy::addAction(EnemyAction newAction) {
    actionList.push_back(std::move(newAction));
}

void Enemy::printNextAction() const {
    if (actionList.empty()) {
        std::cout << getName()
                  << " has no available action.\n";
        return;
    }

    std::cout << getName()
              << " intends to use: "
              << actionList[nextActionIndex].getName()
              << '\n';
}

void Enemy::handleTurnStart() {
    Character::handleTurnStart();
}

void Enemy::handleTurnEnd() {
    Character::handleTurnEnd();
}

int Enemy::getDamage() const {
    return damage;
}