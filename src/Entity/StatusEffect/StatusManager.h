//
// Created by lll on 2026/6/4.
//

#ifndef CARDBATTLE_STATUSMANAGER_H
#define CARDBATTLE_STATUSMANAGER_H
#include <vector>
#include <memory>

#include "StatusEffect.h"


class Character;
class StatusEffect;

class StatusManager {
private:
    std::vector<std::unique_ptr<StatusEffect>> statusEffects;

public:
    StatusManager();

    void addStatus(std::unique_ptr<StatusEffect> statusEffect);

    void removeExpiredStatus();

    void onTurnStart(Character& owner);
    void onTurnEnd(Character& owner);

    int calculateOutgoingDamage(int baseDamage);
    int calculateIncomingDamage(int baseDamage);
    int calculateArmorGain(int baseArmor);

    std::string getStatusText() const;
    void printStatuses() const;
};


#endif //CARDBATTLE_STATUSMANAGER_H
