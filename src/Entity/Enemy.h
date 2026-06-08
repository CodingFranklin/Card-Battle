//
// Created by lll on 2026/5/26.
//

#ifndef CARDBATTLE_ENEMY_H
#define CARDBATTLE_ENEMY_H
#include "Character.h"


class Enemy : public Character{
    private:
        float damage;
        // TODO action list/array
        // Action[] actions;
    public:
        Enemy(const std::string& name, float maxHealth, float damage);

        float getDamage() const;

    protected:
        void handleTurnStart() override;
        void handleTurnEnd() override;
};


#endif //CARDBATTLE_ENEMY_H
