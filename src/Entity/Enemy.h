//
// Created by lll on 2026/5/26.
//

#ifndef CARDBATTLE_ENEMY_H
#define CARDBATTLE_ENEMY_H
#include "Character.h"


class Enemy : public Character{
    private:
        int damage;
        // TODO action list/array
        // Action[] actions;
    public:
        Enemy(const std::string& name, int maxHealth, int damage);

        int getDamage() const;

    protected:
        void handleTurnStart() override;
        void handleTurnEnd() override;
};


#endif //CARDBATTLE_ENEMY_H
