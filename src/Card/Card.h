//
// Created by lll on 2026/5/26.
//

#ifndef CARDBATTLE_CARD_H
#define CARDBATTLE_CARD_H

#include <memory>
#include <string>
#include <vector>

struct ActionContext;
class Effect;
class Player;
class Character;

enum class CardType {
    Attack,     // 攻击牌
    Skill,      // 技能牌
    Ability,    // 能力牌
    Status      // 状态牌
};

class Card {
private:
    std::string name;
    std::string description;
    int cost;
    CardType type;

    std::vector<std::unique_ptr<Effect>> effects;

public:
    Card(
        const std::string& name,
        const std::string& description,
        int cost,
        CardType type
    );

    virtual ~Card();

    bool play(ActionContext& context);

    bool canPlay(const Player& player) const;

    const std::string& getName() const;

    const std::string& getDescription() const;

    int getCost() const;

    CardType getType() const;

    bool requiresSelectedTarget() const;

    void addEffect(std::unique_ptr<Effect> effect);

    virtual std::unique_ptr<Card> clone() const;
};

#endif // CARDBATTLE_CARD_H