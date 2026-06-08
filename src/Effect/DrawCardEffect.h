//
// Created by lll on 2026/6/5.
//

#ifndef CARDBATTLE_DRAWCARDEFFECT_H
#define CARDBATTLE_DRAWCARDEFFECT_H
#include "Effect.h"

class DrawCardEffect : public Effect {
private:
    int qty;
public:
    DrawCardEffect(int qty): qty(qty) {};

    void apply(Player &player, std::vector<Character *> &targets) override {
        player.deckManager.drawCards(qty);
    };

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<DrawCardEffect>(*this);
    }
};


#endif //CARDBATTLE_DRAWCARDEFFECT_H
