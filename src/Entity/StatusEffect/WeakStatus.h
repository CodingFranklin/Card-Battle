//
// Created by lll on 2026/6/4.
//

#ifndef CARDBATTLE_WEAKSTATUS_H
#define CARDBATTLE_WEAKSTATUS_H
#include "StatusEffect.h"


class WeakStatus: public StatusEffect {
public:
    WeakStatus(int value):
        StatusEffect("Weak", value) {}

    int calculateOutgoingDamage(int baseDamage) override {
        return baseDamage * 0.75f;
    }

    void onTurnEnd(Character& owner) override {
        value--;
    }

    std::unique_ptr<StatusEffect> clone() const override {
        return std::make_unique<WeakStatus>(*this);
    }
};

#endif //CARDBATTLE_WEAKSTATUS_H