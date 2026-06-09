//
// Created by lll on 2026/5/27.
//

#ifndef CARDBATTLE_BATTLE_H
#define CARDBATTLE_BATTLE_H
#include <vector>

#include "TurnManager.h"
#include "../Entity/Enemy.h"
#include "../Entity/Player.h"


class Battle {
    private:
        Player& player;
        std::vector<Enemy*> enemies;
        TurnManager turnManager;
        bool battleOver;
    public:
        Battle(Player& player, std::vector<Enemy*>& enemies);

        void start();

    private:
        void runPlayerTurn();
        void runEnemyTurn();

        void playerAct();
        void enemyAct();

        void bindEvents();
        void checkBattleEnd();

        Enemy* chooseEnemyTarget();
        void printBattleStatus() const;
};


#endif //CARDBATTLE_BATTLE_H
