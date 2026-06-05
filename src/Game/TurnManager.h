//
// Created by lll on 2026/5/27.
//

#ifndef CARDBATTLE_TURNMANAGER_H
#define CARDBATTLE_TURNMANAGER_H
#include "Event.h"

enum TurnPhase {
    PlayerTurn,
    EnemyTurn
};

class TurnManager {
    private:
        int turnCount;
        TurnPhase currentTurn;

    public:
        Event onPlayerTurnStart;
        Event onPlayerTurnEnd;
        Event onEnemyTurnStart;
        Event onEnemyTurnEnd;

    public:
        TurnManager();

        void startPlayerTurn();
        void endPlayerTurn();
        void startEnemyTurn();
        void endEnemyTurn();

        int getTurnCount() const;
        TurnPhase getTurnPhase() const;
};


#endif //CARDBATTLE_TURNMANAGER_H
