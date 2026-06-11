#ifndef CARDBATTLE_DECKLOADER_H
#define CARDBATTLE_DECKLOADER_H

#include <string>

class DeckManager;

class DeckLoader {
public:
    DeckLoader() = delete;

    static bool loadMainDeckFromJson(
        DeckManager& deckManager,
        const std::string& cardsFilePath,
        const std::string& starterDeckFilePath
    );
};

#endif // CARDBATTLE_DECKLOADER_H
