//
// Created by lll on 2026/6/9.
//

#include "EnemyAction.h"

#include <iostream>
#include <utility>

EnemyAction::EnemyAction(std::string name)
    : name(std::move(name)) {
}

EnemyAction::EnemyAction(const EnemyAction& other)
    : name(other.name) {
    effects.reserve(other.effects.size());

    for (const auto& effect : other.effects) {
        if (effect != nullptr) {
            effects.push_back(effect->clone());
        }
    }
}

void EnemyAction::addEffect(std::unique_ptr<Effect> effect) {
    effects.push_back(std::move(effect));
}

void EnemyAction::act(ActionContext& context) {
    std::cout << "[DEBUG] "
              << name
              << " effect count: "
              << effects.size()
              << '\n';

    for (const auto& effect : effects) {
        if (effect != nullptr) {
            effect->apply(context);
        }
    }
}

const std::string& EnemyAction::getName() const {
    return name;
}