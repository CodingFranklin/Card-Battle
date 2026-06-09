//
// Created by lll on 2026/6/9.
//

#ifndef CARDBATTLE_GAMETYPE_H
#define CARDBATTLE_GAMETYPE_H

enum class TargetType {
    Single,       // 选择单个目标
    Self,        // 目标是自己
    AllEnemies, // 所有敌人，群攻
    None
};

#endif //CARDBATTLE_GAMETYPE_H
