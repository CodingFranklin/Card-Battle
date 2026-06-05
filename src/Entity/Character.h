//
// Created by lll on 2026/5/26.
//

#ifndef CARDBATTLE_CHARACTER_H
#define CARDBATTLE_CHARACTER_H
#include <string>

#include "StatusEffect/StatusManager.h"

class Character {
    private:
        std::string name;
        float maxHealth;
        float curHealth;
        float armor;
    public:
        Character(const std::string& name, float maxHealth);
        void takeDamage (float damage);
        void dealDamageTo(Character& target, int baseDamage);
        void addArmor(float amount);
        void gainArmor(float baseArmor);
        void clearArmor();
        bool isDead() const;

        void addStatus(std::unique_ptr<StatusEffect> status);

        void beginTurn();
        void endTurn();

        //getter
        const std::string& getName() const;
        float getMaxHealth() const;
        float getCurHealth() const;
        float getArmor() const;
        std::string getStatusText() const;

    protected:
        virtual ~Character() = default;
        virtual void handleTurnStart();
        virtual void handleTurnEnd();

    private:
        StatusManager statusManager;
        int calculateOutgoingDamage(int baseDamage);
        int calculateIncomingDamage(int baseDamage);
        int calculateArmorGain(int baseArmor);

};


#endif //CARDBATTLE_CHARACTER_H
