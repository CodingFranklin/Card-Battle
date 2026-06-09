//
// Created by lll on 2026/6/3.
//

#ifndef CARDBATTLE_DAMAGEEFFECT_H
#define CARDBATTLE_DAMAGEEFFECT_H
#include "Effect.h"
#include "../Game/ActionContext.h"
#include "../Entity/Character.h"

class DamageEffect : public Effect{
private:
    int damage;

public:
    DamageEffect(int damage, TargetType targetType): Effect(targetType), damage(damage) {};

    void apply(ActionContext& context) override {
        auto targets = resolveTargets(context);

        std::cout << "[DEBUG] damage targets: "
             << targets.size()
             << '\n';


        for (Character* target : targets) {
            context.source.dealDamageTo(*target, damage);
        }
    };

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<DamageEffect>(*this);
    };
};


#endif //CARDBATTLE_DAMAGEEFFECT_H
