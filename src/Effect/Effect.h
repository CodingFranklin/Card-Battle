//
// Created by lll on 2026/6/3.
//

#ifndef CARDBATTLE_CARDEFFECT_H
#define CARDBATTLE_CARDEFFECT_H

#include <vector>
#include <memory>

#include "../Entity/Character.h"
#include "../Entity/Player.h"


enum class TargetType;

class Effect {
private:
    TargetType targetType;

public:
    virtual ~Effect() = default;

    Effect(TargetType targetType) : targetType(targetType) {}

    virtual void apply(Player& player, std::vector<Character*>& targets) = 0;

    virtual std::unique_ptr<Effect> clone() const = 0;

    TargetType getTargetType() const {return targetType;};

};


#endif //CARDBATTLE_CARDEFFECT_H
