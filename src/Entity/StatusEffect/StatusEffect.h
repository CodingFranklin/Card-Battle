//
// Created by lll on 2026/6/4.
//

#ifndef CARDBATTLE_STATUSEFFECT_H
#define CARDBATTLE_STATUSEFFECT_H
#include <memory>
#include <string>



class Character;

class StatusEffect {
protected:
    std::string name;
    int value;

public:
    StatusEffect(const std::string& name, int value);

    virtual ~StatusEffect() = default;

    std::string& getName();

    int getValue();

    void addValue(int amount);

    bool isExpired() const;

    virtual void onTurnStart(Character& owner);
    virtual void onTurnEnd(Character& owner);

    virtual int calculateOutgoingDamage(int baseDamage);
    virtual int calculateIncomingDamage(int baseDamage);
    virtual int calculateArmorGain(int baseArmor);

    virtual std::unique_ptr<StatusEffect> clone() const = 0;
};


#endif //CARDBATTLE_STATUSEFFECT_H
