//
// Created by lll on 2026/6/4.
//

#ifndef CARDBATTLE_POISONEFFECT_H
#define CARDBATTLE_POISONEFFECT_H
#include "StatusEffect.h"
#include "../Character.h"


class PoisonStatus : public StatusEffect {
public:
    PoisonStatus(int value):
        StatusEffect("Poison", value){}

    void onTurnStart(Character& owner) override {
        owner.takeDamage(value);
        value--;
    };

    std::unique_ptr<StatusEffect> clone() const override {
        return std::make_unique<PoisonStatus>(*this);
    }
};


#endif //CARDBATTLE_POISONEFFECT_H
