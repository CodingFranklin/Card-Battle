//
// Created by lll on 2026/6/3.
//

#ifndef CARDBATTLE_DAMAGEEFFECT_H
#define CARDBATTLE_DAMAGEEFFECT_H
#include "CardEffect.h"
#include "../../Entity/Player.h"

class DamageEffect : public CardEffect{
private:
    int damage;

public:
    DamageEffect(int damage): damage(damage) {};

    void apply(Player& player, std::vector<Character*>& targets) override {
        for (Character* target : targets) {
            if (target != nullptr && !target->isDead()) {
                player.dealDamageTo(*target, damage);
            }
        }
    };

    std::unique_ptr<CardEffect> clone() const override {
        return std::make_unique<DamageEffect>(*this);
    };
};


#endif //CARDBATTLE_DAMAGEEFFECT_H
