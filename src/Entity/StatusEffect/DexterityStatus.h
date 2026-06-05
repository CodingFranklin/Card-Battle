//
// Created by lll on 2026/6/4.
//

#ifndef CARDBATTLE_DEXTERITYSTATUS_H
#define CARDBATTLE_DEXTERITYSTATUS_H
#include "StatusEffect.h"



class DexterityStatus : public StatusEffect {
public:
    DexterityStatus(int value):
        StatusEffect("Dexterity", value) {}

    int calculateArmorGain(int baseArmor) override {
        return baseArmor + value;
    }

    std::unique_ptr<StatusEffect> clone() const override {
        return std::make_unique<DexterityStatus>(*this);
    }
};

#endif //CARDBATTLE_DEXTERITYSTATUS_H