//
// Created by lll on 2026/5/26.
//

#include "Card.h"

#include "../Entity/Player.h"
#include "../Entity/Character.h"

#include <iostream>
#include <utility>

Card::Card(
    const std::string& name,
    const std::string& description,
    int cost,
    CardType type,
    TargetType targetType
)
    : name(name),
      description(description),
      cost(cost),
      type(type),
      targetType(targetType)
{
}

bool Card::canPlay(const Player& player) const {
    return player.getEnergy() >= cost;
}

bool Card::play(Player &player, std::vector<Character *> &targets) {
    if (!canPlay(player)) {
        std::cout << "Not enough energy." << std::endl;
        return false;
    }

    player.spendEnergy(cost);

    for (const auto& effect : effects) {
        if (effect != nullptr) {
            effect->apply(player, targets);
        }
    }

    return true;
}

void Card::addEffect(std::unique_ptr<Effect> effect) {
    effects.push_back(std::move(effect));
}

std::unique_ptr<Card> Card::clone() const {
    auto newCard = std::make_unique<Card>(
        name,
        description,
        cost,
        type,
        targetType
    );

    for (const auto& effect : effects) {
        if (effect != nullptr) {
            newCard->addEffect(effect->clone());
        }
    }

    return newCard;
}

const std::string& Card::getName() const {
    return name;
}

const std::string& Card::getDescription() const {
    return description;
}

int Card::getCost() const {
    return cost;
}

CardType Card::getType() const {
    return type;
}

TargetType Card::getTargetType() const {
    return targetType;
}

bool Card::requiresSelectedTarget() const {
    for (const auto& effect : effects) {
        if (effect != nullptr &&
            effect->getTargetType() == TargetType::Enemy) {
            return true;
            }
    }

    return false;
}