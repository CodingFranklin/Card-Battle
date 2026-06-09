//
// Created by lll on 2026/5/26.
//

#include "Enemy.h"

Enemy::Enemy(const std::string &name, int maxHealth, int damage):
    Character(name, maxHealth),
    damage(damage)
{}

void Enemy::handleTurnStart() {
    Character::handleTurnStart();
}

void Enemy::handleTurnEnd() {
    Character::handleTurnEnd();
}

int Enemy::getDamage() const {
    return damage;
}