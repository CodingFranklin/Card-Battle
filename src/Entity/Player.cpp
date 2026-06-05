//
// Created by lll on 2026/5/26.
//

#include "Player.h"

#include <iostream>

#include "../Card/Card.h"

Player::Player(const std::string& name, float maxHealth, int maxEnergy):
    Character(name, maxHealth),
    curEnergy(maxEnergy),
    maxEnergy(maxEnergy),
    deckManager()
{}

bool Player::spendEnergy(int amount) {
    if (curEnergy < amount) {
        return false;
    }
    curEnergy -= amount;
    return true;
}

void Player::reloadEnergy() { curEnergy = maxEnergy; }

void Player::gainEnergy(int amount) { curEnergy += amount; }

void Player::handleTurnStart() {
    Character::handleTurnStart();
    reloadEnergy();
}
void Player::handleTurnEnd() {
    Character::handleTurnEnd();
    // ability activate
}


int Player::getEnergy() const { return curEnergy; }

int Player::getMaxEnergy() const { return maxEnergy; }
