//
// Created by lll on 2026/5/26.
//

#ifndef CARDBATTLE_ENEMY_H
#define CARDBATTLE_ENEMY_H
#include <vector>

#include "Character.h"
#include "../Action/EnemyAction.h"

struct ActionContext;


class Enemy : public Character{
private:
    int damage;

    std::vector<EnemyAction> actionList;
    std::size_t nextActionIndex = 0;

public:
    Enemy(const std::string& name, int maxHealth, int damage);

    void doAction(ActionContext& context);

    void addAction(EnemyAction newAction);

    [[nodiscard]] int getDamage() const;

    void printNextAction() const;

protected:
    void handleTurnStart() override;
    void handleTurnEnd() override;
};


#endif //CARDBATTLE_ENEMY_H
