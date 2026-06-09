//
// Created by lll on 2026/6/4.
//

#ifndef CARDBATTLE_DEXTERITYEFFECT_H
#define CARDBATTLE_DEXTERITYEFFECT_H
#include "Effect.h"

class GainStatusEffect : public Effect{
private:
    std::unique_ptr<StatusEffect> status;

public:
    GainStatusEffect(std::unique_ptr<StatusEffect> status, TargetType targetType):
        Effect(targetType), status(std::move(status)) {};

    void apply(Player& player, std::vector<Character*>& targets) override {
        for (Character* target : targets) {
            if (target != nullptr && !target->isDead()) {
                target->addStatus(status->clone());
            }
        }
    };

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<GainStatusEffect>(status->clone(), getTargetType());
    };
};

#endif //CARDBATTLE_DEXTERITYEFFECT_H