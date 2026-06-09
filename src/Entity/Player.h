//
// Created by lll on 2026/5/26.
//

#ifndef CARDBATTLE_PLAYER_H
#define CARDBATTLE_PLAYER_H
#include "Character.h"
#include "Enemy.h"
#include "../Deck/DeckManager.h"


class Card;

class Player : public Character {
    private:
        // energy
        int curEnergy;
        int maxEnergy;
    public:
        // TODO card decks
        DeckManager deckManager;

        // TODO potions

        // TODO objects

    public:
        Player(const std::string& name, int maxHealth, int maxEnergy);
        bool spendEnergy(int amount);
        void reloadEnergy();
        void gainEnergy(int amount);

        // getter
        int getEnergy() const;
        int getMaxEnergy() const;

    protected:
        void handleTurnStart() override;
        void handleTurnEnd() override;
};


#endif //CARDBATTLE_PLAYER_H
