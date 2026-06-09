//
// Created by lll on 2026/5/28.
//

#ifndef CARDBATTLE_DECKMANAGER_H
#define CARDBATTLE_DECKMANAGER_H
#include <memory>
#include <vector>

#include "../Card/Card.h"
class Character;
class Player;


class DeckManager {
    public:
    std::vector<std::unique_ptr<Card>> mainDeck;

    private:
    std::vector<std::unique_ptr<Card>> drawPile;

    std::vector<std::unique_ptr<Card>> handCards;

    std::vector<std::unique_ptr<Card>> discardPile;

public:
    DeckManager();

    void resetDrawPileFromMainDeck();

    // drawPile -> handCards
    void drawCards(int qty);

    // DiscardPile -> drawPile
    void reshuffleDiscardPileIntoDrawPile();

    void shuffleDrawPile();

    bool playHandCard(int index, ActionContext& context);

    // Hand -> discardPile
    void discardHandCard(int index, bool discardAll = false);

    void addOneCardToMainDeck(std::unique_ptr<Card> card);

    void printHandCards() const;

    int getHandCardsSize() const;

    int getDrawPileSize() const;

    Card* getHandCard(int index) const;
};


#endif //CARDBATTLE_DECKMANAGER_H
