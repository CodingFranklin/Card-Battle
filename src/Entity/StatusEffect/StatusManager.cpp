//
// Created by lll on 2026/6/4.
//

#include "StatusManager.h"

#include <filesystem>
#include <iostream>


StatusManager::StatusManager(){}

void StatusManager::addStatus(std::unique_ptr<StatusEffect> statusEffect) {
    if (statusEffect == nullptr) {return;}

    // 如果该状态已存在则增加层数
    for (auto& existingStatus : statusEffects) {
        if (existingStatus->getName() == statusEffect->getName()) {
            existingStatus->addValue(statusEffect->getValue());
            return;
        }
    }

    // 如果没有该状态则增加新状态
    statusEffects.push_back(std::move(statusEffect));
}

void StatusManager::onTurnStart(Character& owner) {
    for (auto& status : statusEffects) {
        status->onTurnStart(owner);
    }

    removeExpiredStatus();
}


void StatusManager::onTurnEnd(Character& owner) {
    for (auto& status : statusEffects) {
        status->onTurnEnd(owner);
    }

    removeExpiredStatus();
}

int StatusManager::calculateOutgoingDamage(int baseDamage) {
    int finalDamage = baseDamage;
    for (auto& status : statusEffects) {
        finalDamage = status->calculateOutgoingDamage(finalDamage);
    }

    return finalDamage;
}

int StatusManager::calculateIncomingDamage(int baseDamage) {
    int finalDamage = baseDamage;
    for (auto& status : statusEffects) {
        finalDamage = status->calculateIncomingDamage(finalDamage);
    }

    return finalDamage;
}

int StatusManager::calculateArmorGain(int baseArmor) {
    int finalArmor = baseArmor;
    for (auto& status : statusEffects) {
        finalArmor = status->calculateArmorGain(finalArmor);
    }

    return finalArmor;
}



void StatusManager::removeExpiredStatus() {
    for (int i = 0; i < statusEffects.size(); i++) {
        if (statusEffects[i]->isExpired()) {
            std::cout<<"Status "<<statusEffects[i]->getName()<< " expired" <<std::endl;
            statusEffects.erase(statusEffects.begin() + i);
        }
    }
}

std::string StatusManager::getStatusText() const {
    if (statusEffects.empty()) {
        return "None";
    }

    std::ostringstream oss;

    for (int i = 0; i < static_cast<int>(statusEffects.size()); i++) {
        oss << statusEffects[i]->getName()
            << "："
            << statusEffects[i]->getValue();

        if (i != static_cast<int>(statusEffects.size()) - 1) {
            oss << "，";
        }
    }

    return oss.str();
}

void StatusManager::printStatuses() const {
    if (statusEffects.empty()) {
        std::cout << "No status effects." << std::endl;
        return;
    }

    for (const auto& status : statusEffects) {
        std::cout << status->getName()
                  << ": "
                  << status->getValue()
                  << std::endl;
    }
}