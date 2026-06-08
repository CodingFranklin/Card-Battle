//
// Created by lll on 2026/6/5.
//

#ifndef CARDBATTLE_GAINENERGYEFFECT_H
#define CARDBATTLE_GAINENERGYEFFECT_H
#include "Effect.h"

class GainEnergyEffect: public Effect {
private:
    int amount;
public:
    GainEnergyEffect(int amount): amount(amount) {}

    void apply(Player &player, std::vector<Character *> &targets) override {
        player.gainEnergy(amount);
    };

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<GainEnergyEffect>(*this);
    };
};

#endif //CARDBATTLE_GAINENERGYEFFECT_H
