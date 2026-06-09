//
// Created by lll on 2026/6/9.
//
#include "Effect.h"
#include "../Game/ActionContext.h"
#include "../Entity/Character.h"
#include "../Entity/Enemy.h"

Effect::Effect(TargetType targetType)
    : targetType(targetType) {
}

TargetType Effect::getTargetType() const {
    return targetType;
}

std::vector<Character*> Effect::resolveTargets(
    const ActionContext& context
) const {
    std::vector<Character*> targets;

    switch (targetType) {
        case TargetType::Self:
            targets.push_back(&context.source);
            break;

        case TargetType::Single:
            if (context.selectedTarget != nullptr &&
                !context.selectedTarget->isDead()) {
                targets.push_back(context.selectedTarget);
                }
            break;

        case TargetType::AllEnemies:
            for (Enemy* enemy : context.enemies) {
                if (enemy != nullptr && !enemy->isDead()) {
                    targets.push_back(enemy);
                }
            }
            break;

        case TargetType::None:
            break;
    }

    return targets;
}