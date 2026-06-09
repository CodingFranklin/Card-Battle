//
// Created by lll on 2026/5/26.
//

#include <iostream>
#include <utility>

#include "Card.h"
#include "../Game/GameType.h"
#include "../Entity/Player.h"
#include "../Effect/Effect.h"
#include "../Game/ActionContext.h"

Card::Card(
    const std::string& name,
    const std::string& description,
    int cost,
    CardType type
)
    : name(name),
      description(description),
      cost(cost),
      type(type)
{}

Card::~Card() = default;

bool Card::canPlay(const Player& player) const {
    return player.getEnergy() >= cost;
}

bool Card::play(ActionContext& context) {
    if (!canPlay(context.player)) {
        std::cout << "Not enough energy." << std::endl;
        return false;
    }

    context.player.spendEnergy(cost);

    for (const auto& effect : effects) {
        if (effect != nullptr) {
            effect->apply(context);
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
        type
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

bool Card::requiresSelectedTarget() const {
    for (const auto& effect : effects) {
        if (effect != nullptr &&
            effect->getTargetType() == TargetType::Single) {
            return true;
            }
    }

    return false;
}