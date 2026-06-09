//
// Created by lll on 2026/6/9.
//

#ifndef CARDBATTLE_ACTIONCONTEXT_H
#define CARDBATTLE_ACTIONCONTEXT_H

#pragma once

#include <vector>

class Character;
class Player;
class Enemy;

struct ActionContext {
    Character& source;                 // 玩家或当前行动的敌人
    Player& player;                    // 当前战斗的玩家
    std::vector<Enemy*>& enemies;      // 当前战斗的全部敌人
    Character* selectedTarget = nullptr;
};

#endif //CARDBATTLE_ACTIONCONTEXT_H
