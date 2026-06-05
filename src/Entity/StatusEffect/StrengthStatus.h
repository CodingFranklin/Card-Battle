//
// Created by lll on 2026/6/4.
//

#ifndef CARDBATTLE_STRENGTHEFFECT_H
#define CARDBATTLE_STRENGTHEFFECT_H
#include "StatusEffect.h"


class StrengthStatus: public StatusEffect {
public:
    StrengthStatus(int value):
        StatusEffect("Strength", value) {}

    int calculateOutgoingDamage(int baseDamage) override {
        return baseDamage + value;
    }

    std::unique_ptr<StatusEffect> clone() const override {
        return std::make_unique<StrengthStatus>(*this);
    }
};

#endif //CARDBATTLE_STRENGTHEFFECT_H