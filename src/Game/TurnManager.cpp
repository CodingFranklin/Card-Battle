//
// Created by lll on 2026/5/27.
//

#include "TurnManager.h"

#include <iostream>
#include <ostream>

#include "../Entity/Player.h"

TurnManager::TurnManager():
    turnCount(1), currentTurn(PlayerTurn)
{}

void TurnManager::startPlayerTurn() {
    std::cout << "\n=== Turn " << turnCount << " ===" << std::endl;
    std::cout << "-- Player Turn Start --" << std::endl;

    currentTurn = PlayerTurn;
    onPlayerTurnStart.invoke();
}

void TurnManager::endPlayerTurn() {
    if (currentTurn != PlayerTurn) {
        std::cout << "Error: currentTurn does not match" << std::endl;
        return;
    }
    onPlayerTurnEnd.invoke();

    std::cout << "-- Player Turn End --" << std::endl;
}

void TurnManager::startEnemyTurn() {
    currentTurn = EnemyTurn;

    std::cout << "-- Enemy Turn Start --" << std::endl;

    onEnemyTurnStart.invoke();
}

void TurnManager::endEnemyTurn() {
    onEnemyTurnEnd.invoke();

    std::cout << "-- Enemy Turn End --" << std::endl;

    turnCount++;
}


int TurnManager::getTurnCount() const {return turnCount;}
TurnPhase TurnManager::getTurnPhase() const {return currentTurn;}