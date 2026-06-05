//
// Created by lll on 2026/6/4.
//

#include "StatusEffect.h"

StatusEffect::StatusEffect(const std::string& name, int value):
    name(name), value(value)
{}

std::string& StatusEffect::getName() {
    return name;
}

int StatusEffect::getValue() {
    return value;
}

void StatusEffect::addValue(int amount) {
    value += amount;
}

bool StatusEffect::isExpired() const {
    return value <= 0;
}

void StatusEffect::onTurnEnd(Character &character) {

}

void StatusEffect::onTurnStart(Character &character) {

}

int StatusEffect::calculateIncomingDamage(int baseDamage) {
    return baseDamage;
}

int StatusEffect::calculateOutgoingDamage(int baseDamage) {
    return baseDamage;
}

int StatusEffect::calculateArmorGain(int baseArmor) {
    return baseArmor;
}
