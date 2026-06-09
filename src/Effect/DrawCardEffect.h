//
// Created by lll on 2026/6/5.
//

#ifndef CARDBATTLE_DRAWCARDEFFECT_H
#define CARDBATTLE_DRAWCARDEFFECT_H
#include "Effect.h"
#include "../Entity/Player.h"

class DrawCardEffect : public Effect {
private:
    int qty;
public:
    DrawCardEffect(int qty, TargetType targetType): Effect(targetType), qty(qty) {};

    void apply(ActionContext& context) override {
        context.player.deckManager.drawCards(qty);
    };

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<DrawCardEffect>(*this);
    }
};


#endif //CARDBATTLE_DRAWCARDEFFECT_H
