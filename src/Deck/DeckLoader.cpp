#include "DeckLoader.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "DeckManager.h"
#include "../Card/Card.h"
#include "../Effect/DamageEffect.h"
#include "../Effect/DrawCardEffect.h"
#include "../Effect/GainArmorEffect.h"
#include "../Effect/GainEnergyEffect.h"
#include "../Effect/GainStatusEffect.h"
#include "../Entity/StatusEffect/DexterityStatus.h"
#include "../Entity/StatusEffect/PoisonStatus.h"
#include "../Entity/StatusEffect/StrengthStatus.h"
#include "../Entity/StatusEffect/WeakStatus.h"
#include "../Entity/StatusEffect/VulnerableStatus.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace {
    std::optional<std::filesystem::path> findExistingPath(const std::string& relativePath) {
        std::vector<std::filesystem::path> candidates = {
            std::filesystem::path(relativePath),
            std::filesystem::path("src") / relativePath,
            std::filesystem::path("..") / relativePath,
            std::filesystem::path("..") / "src" / relativePath
        };

        for (const auto& candidate : candidates) {
            if (std::filesystem::exists(candidate)) {
                return candidate;
            }
        }
        return std::nullopt;
    }

    bool loadJsonFile(const std::filesystem::path& path, json& outJson) {
        std::ifstream input(path);
        if (!input.is_open()) {
            std::cerr << "Failed to open JSON file: " << path << std::endl;
            return false;
        }

        try {
            input >> outJson;
        } catch (const std::exception& ex) {
            std::cerr << "Failed to parse JSON file '" << path << "': " << ex.what() << std::endl;
            return false;
        }

        return true;
    }

    bool getStringField(
        const json& node,
        const std::vector<std::string>& keys,
        std::string& outValue,
        std::string& errorMessage
    ) {
        for (const auto& key : keys) {
            if (node.contains(key) && node[key].is_string()) {
                outValue = node[key].get<std::string>();
                return true;
            }
        }

        std::ostringstream oss;
        oss << "Required string field missing: ";
        for (int i = 0; i < static_cast<int>(keys.size()); i++) {
            oss << keys[i];
            if (i + 1 < static_cast<int>(keys.size())) {
                oss << " or ";
            }
        }
        errorMessage = oss.str();
        return false;
    }

    bool getIntField(
        const json& node,
        const std::string& key,
        int& outValue,
        std::string& errorMessage
    ) {
        if (!node.contains(key)) {
            errorMessage = "Required integer field missing: " + key;
            return false;
        }
        if (!node[key].is_number_integer()) {
            errorMessage = "Field '" + key + "' must be an integer.";
            return false;
        }
        outValue = node[key].get<int>();
        return true;
    }

    std::optional<CardType> parseCardType(const std::string& value) {
        if (value == "Attack") {
            return CardType::Attack;
        }
        if (value == "Skill") {
            return CardType::Skill;
        }
        if (value == "Ability") {
            return CardType::Ability;
        }
        if (value == "Status") {
            return CardType::Status;
        }
        return std::nullopt;
    }

    std::optional<TargetType> parseTargetType(const std::string& value) {
        if (value == "Single") {
            return TargetType::Single;
        }
        if (value == "Self") {
            return TargetType::Self;
        }
        if (value == "AllEnemies") {
            return TargetType::AllEnemies;
        }
        if (value == "None") {
            return TargetType::None;
        }
        return std::nullopt;
    }

    std::unique_ptr<StatusEffect> createStatusEffectFromJson(
        const json& effectJson,
        std::string& errorMessage
    ) {
        std::string statusType;
        if (!getStringField(effectJson, {"status_type", "status"}, statusType, errorMessage)) {
            return nullptr;
        }

        int value = 0;
        if (!getIntField(effectJson, "value", value, errorMessage)) {
            return nullptr;
        }

        if (statusType == "Poison") {
            return std::make_unique<PoisonStatus>(value);
        }
        if (statusType == "Strength") {
            return std::make_unique<StrengthStatus>(value);
        }
        if (statusType == "Weak") {
            return std::make_unique<WeakStatus>(value);
        }
        if (statusType == "Vulnerable") {
            return std::make_unique<VulnerableStatus>(value);
        }
        if (statusType == "Dexterity") {
            return std::make_unique<DexterityStatus>(value);
        }

        errorMessage = "Unknown status type: " + statusType;
        return nullptr;
    }

    std::unique_ptr<Effect> createEffectFromJson(
        const json& effectJson,
        std::string& errorMessage
    ) {
        std::string effectType;
        if (!getStringField(effectJson, {"effect_type", "type"}, effectType, errorMessage)) {
            return nullptr;
        }

        std::string targetValue;
        if (!getStringField(effectJson, {"target_type", "target"}, targetValue, errorMessage)) {
            return nullptr;
        }

        auto targetType = parseTargetType(targetValue);
        if (!targetType.has_value()) {
            errorMessage = "Unknown target type: " + targetValue;
            return nullptr;
        }

        if (effectType == "DealDamage") {
            int value = 0;
            if (!getIntField(effectJson, "value", value, errorMessage)) {
                return nullptr;
            }
            return std::make_unique<DamageEffect>(value, *targetType);
        }

        if (effectType == "GainArmor") {
            int value = 0;
            if (!getIntField(effectJson, "value", value, errorMessage)) {
                return nullptr;
            }
            return std::make_unique<GainArmorEffect>(value, *targetType);
        }

        if (effectType == "GainEnergy") {
            int value = 0;
            if (!getIntField(effectJson, "value", value, errorMessage)) {
                return nullptr;
            }
            return std::make_unique<GainEnergyEffect>(value, *targetType);
        }

        if (effectType == "DrawCard") {
            int value = 0;
            if (!getIntField(effectJson, "value", value, errorMessage)) {
                return nullptr;
            }
            return std::make_unique<DrawCardEffect>(value, *targetType);
        }

        if (effectType == "GainStatus") {
            auto statusEffect = createStatusEffectFromJson(effectJson, errorMessage);
            if (!statusEffect) {
                return nullptr;
            }
            return std::make_unique<GainStatusEffect>(std::move(statusEffect), *targetType);
        }

        errorMessage = "Unknown effect type: " + effectType;
        return nullptr;
    }

    std::unique_ptr<Card> createCardFromTemplate(
        const std::string& cardId,
        const json& cardJson,
        std::string& errorMessage
    ) {
        std::string name;
        if (!getStringField(cardJson, {"name"}, name, errorMessage)) {
            return nullptr;
        }

        std::string description;
        if (cardJson.contains("description") && cardJson["description"].is_string()) {
            description = cardJson["description"].get<std::string>();
        }

        std::string typeValue;
        if (!getStringField(cardJson, {"card_type", "type"}, typeValue, errorMessage)) {
            return nullptr;
        }

        auto cardType = parseCardType(typeValue);
        if (!cardType.has_value()) {
            errorMessage = "Unknown card type: " + typeValue;
            return nullptr;
        }

        int cost = 0;
        if (!getIntField(cardJson, "cost", cost, errorMessage)) {
            return nullptr;
        }

        auto card = std::make_unique<Card>(name, description, cost, *cardType);

        if (cardJson.contains("effects")) {
            if (!cardJson["effects"].is_array()) {
                errorMessage = "Card '" + cardId + "' has invalid effects array.";
                return nullptr;
            }
            for (const auto& effectJson : cardJson["effects"]) {
                auto effect = createEffectFromJson(effectJson, errorMessage);
                if (!effect) {
                    return nullptr;
                }
                card->addEffect(std::move(effect));
            }
        }

        return card;
    }
}

bool DeckLoader::loadMainDeckFromJson(
    DeckManager& deckManager,
    const std::string& cardsFilePath,
    const std::string& starterDeckFilePath
) {
    auto cardsFile = findExistingPath(cardsFilePath);
    if (!cardsFile.has_value()) {
        std::cerr << "cards.json not found. Searched for: " << cardsFilePath << " and common relative paths." << std::endl;
        return false;
    }

    auto starterFile = findExistingPath(starterDeckFilePath);
    if (!starterFile.has_value()) {
        std::cerr << "starter_deck.json not found. Searched for: " << starterDeckFilePath << " and common relative paths." << std::endl;
        return false;
    }

    json cardsData;
    if (!loadJsonFile(cardsFile.value(), cardsData)) {
        return false;
    }

    json starterData;
    if (!loadJsonFile(starterFile.value(), starterData)) {
        return false;
    }

    if (!cardsData.is_object()) {
        std::cerr << "cards.json must contain a top-level object with card templates." << std::endl;
        return false;
    }

    if (!starterData.contains("cards") || !starterData["cards"].is_array()) {
        std::cerr << "starter_deck.json must contain a top-level array field named 'cards'." << std::endl;
        return false;
    }

    for (const auto& entry : starterData["cards"]) {
        if (!entry.is_object()) {
            std::cerr << "Each starter deck entry must be an object." << std::endl;
            return false;
        }

        std::string cardId;
        std::string errorMessage;
        if (!getStringField(entry, {"cardId"}, cardId, errorMessage)) {
            std::cerr << errorMessage << std::endl;
            return false;
        }

        int quantity = 0;
        if (!getIntField(entry, "quantity", quantity, errorMessage)) {
            std::cerr << errorMessage << std::endl;
            return false;
        }

        if (quantity <= 0) {
            std::cerr << "starter_deck.json entry '" << cardId << "' has invalid quantity: " << quantity << ". Must be greater than 0." << std::endl;
            return false;
        }

        if (!cardsData.contains(cardId)) {
            std::cerr << "starter_deck.json references unknown cardId: " << cardId << std::endl;
            return false;
        }

        const auto& cardTemplate = cardsData[cardId];
        for (int i = 0; i < quantity; ++i) {
            std::string errorMessage;
            auto card = createCardFromTemplate(cardId, cardTemplate, errorMessage);
            if (!card) {
                std::cerr << "Failed to create card '" << cardId << "': " << errorMessage << std::endl;
                return false;
            }
            deckManager.addOneCardToMainDeck(std::move(card));
        }
    }

    deckManager.resetDrawPileFromMainDeck();
    return true;
}
