//
// Created by lll on 2026/6/3.
//

#ifndef CARDBATTLE_GAINARMOREFFECT_H
#define CARDBATTLE_GAINARMOREFFECT_H
#include <memory>
#include <vector>

#include "Effect.h"

class GainArmorEffect: public Effect {
private:
    int armor;

public:
    GainArmorEffect(int armor, TargetType targetType): Effect(targetType), armor(armor) {};

    void apply(Player& player, std::vector<Character*>& targets) override {
        for (Character* target : targets) {
            if (target != nullptr && !target->isDead()) {
                target->gainArmor(armor);
            }
        }
    };

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<GainArmorEffect>(*this);
    }
};

#endif //CARDBATTLE_GAINARMOREFFECT_H