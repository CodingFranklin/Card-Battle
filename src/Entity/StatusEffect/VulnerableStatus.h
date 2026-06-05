//
// Created by lll on 2026/6/4.
//

#ifndef CARDBATTLE_VULNERABLESTATUS_H
#define CARDBATTLE_VULNERABLESTATUS_H
#include "StatusEffect.h"


class VulnerableStatus: public StatusEffect {
public:
    VulnerableStatus(int value):
        StatusEffect("Vulnerable", value) {}

    int calculateIncomingDamage(int baseDamage) override {
        return baseDamage + baseDamage * 0.5f;
    }

    void onTurnEnd(Character& owner) override {
        value--;
    }

    std::unique_ptr<StatusEffect> clone() const override {
        return std::make_unique<VulnerableStatus>(*this);
    }
};

#endif //CARDBATTLE_VULNERABLESTATUS_H