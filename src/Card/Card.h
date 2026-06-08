//
// Created by lll on 2026/5/26.
//

#ifndef CARDBATTLE_CARD_H
#define CARDBATTLE_CARD_H

#include <memory>
#include <string>
#include <vector>


#include "../Effect/Effect.h"
class Player;
class Character;

enum class CardType {
    Attack,     // 攻击牌
    Skill,      // 技能牌
    Ability,    // 能力牌
    Status      // 状态牌
};

enum class TargetType {
    Enemy,       // 选择一个敌人
    Self,        // 目标是玩家自己
    AllEnemies, // 所有敌人，群攻
    None
};

class Card {
private:
    std::string name;
    std::string description;
    int cost;
    CardType type;
    TargetType targetType;

    std::vector<std::unique_ptr<Effect>> effects;

public:
    Card(
        const std::string& name,
        const std::string& description,
        int cost,
        CardType type,
        TargetType targetType
    );

    virtual ~Card() = default;

    bool play(Player &player, std::vector<Character *> &targets);

    bool canPlay(const Player& player) const;

    const std::string& getName() const;
    const std::string& getDescription() const;
    int getCost() const;
    CardType getType() const;
    TargetType getTargetType() const;

    void addEffect(std::unique_ptr<Effect> effect);

    virtual std::unique_ptr<Card> clone() const;
};

#endif // CARDBATTLE_CARD_H