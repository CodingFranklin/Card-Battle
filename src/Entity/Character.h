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
        int maxHealth;
        int curHealth;
        int armor;
    public:
        Character(const std::string& name, int maxHealth);
        void takeDamage (int damage);
        void dealDamageTo(Character& target, int baseDamage);
        void addArmor(int amount);
        void gainArmor(int baseArmor);
        void clearArmor();
        bool isDead() const;

        void addStatus(std::unique_ptr<StatusEffect> status);

        void beginTurn();
        void endTurn();

        //getter
        const std::string& getName() const;
        int getMaxHealth() const;
        int getCurHealth() const;
        int getArmor() const;
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
