//
// Created by lll on 2026/6/3.
//

#ifndef CARDBATTLE_CARDEFFECT_H
#define CARDBATTLE_CARDEFFECT_H

#include <vector>
#include <memory>

#include "../Entity/Character.h"
#include "../Entity/Player.h"


class Effect {
public:
    virtual ~Effect() = default;
    virtual void apply(Player& player, std::vector<Character*>& targets) = 0;
    virtual std::unique_ptr<Effect> clone() const = 0;

};


#endif //CARDBATTLE_CARDEFFECT_H
