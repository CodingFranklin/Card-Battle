//
// Created by lll on 2026/6/3.
//

#ifndef CARDBATTLE_CARDEFFECT_H
#define CARDBATTLE_CARDEFFECT_H

#pragma once

#include <memory>
#include <vector>
#include "../Game/GameType.h"

class Character;
class ActionContext;

class Effect {
private:
    TargetType targetType;

protected:
    std::vector<Character*> resolveTargets(
        const ActionContext& context
    ) const;

public:
    explicit Effect(TargetType targetType);

    virtual ~Effect() = default;

    virtual void apply(ActionContext& context) = 0;

    [[nodiscard]] TargetType getTargetType() const;

    virtual std::unique_ptr<Effect> clone() const = 0;
};


#endif //CARDBATTLE_CARDEFFECT_H
