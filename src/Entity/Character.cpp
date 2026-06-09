//
// Created by lll on 2026/5/26.
//

#include "Character.h"


#include <iostream>
#include <ostream>
#include <string>

/**
 * 创建角色并初始化基础属性
 * @param name 角色名称
 * @param maxHealth 角色最大生命值，同时作为初始生命值
 */
Character::Character(const std::string& name, int maxHealth):
    name(name),
    maxHealth(maxHealth),
    curHealth(maxHealth),
    armor(0)
{}

/**
 * 承受最终伤害，优先使用护盾抵消伤害，剩余伤害扣除生命值
 * 该方法不会再经过状态效果计算
 * @param damage 已经计算完成的最终伤害值
 */
void Character::takeDamage(int damage) {
    std::cout << name << " receive damage: " << damage << std::endl;

    if (armor >= damage) {
        armor -= damage;
    } else {
        curHealth -= damage - armor;

        if (curHealth <= 0) {
            curHealth = 0;
        }

        std::cout << name
                  << " actual damage: "
                  << damage - armor
                  << std::endl;

        clearArmor();
    }
}

/**
 * 对目标造成经过攻击者和目标状态计算后的最终伤害
 * @param target 承受伤害的目标角色
 * @param baseDamage 未经过状态效果计算的基础伤害
 */
void Character::dealDamageTo(Character& target, int baseDamage) {
    int finalDamage = statusManager.calculateOutgoingDamage(baseDamage);
    finalDamage = target.statusManager.calculateIncomingDamage(finalDamage);

    target.takeDamage(finalDamage);
}

/**
 * 直接增加指定数量的护盾，不经过状态效果计算
 * @param amount 直接增加的护盾值
 */
void Character::addArmor(int amount) {
    armor += amount;

    std::cout << name
              << " gain armor: "
              << amount
              << std::endl;
}

/**
 * 获得经过角色状态效果计算后的最终护盾
 * @param baseArmor 未经过状态效果计算的基础护盾值
 */
void Character::gainArmor(int baseArmor) {
    int finalArmor = statusManager.calculateArmorGain(baseArmor);

    armor += finalArmor;

    std::cout << name
              << " gain armor: "
              << finalArmor
              << std::endl;
}

/**
 * 清除角色当前的全部护盾
 */
void Character::clearArmor() {
    armor = 0;
}

/**
 * 判断角色是否已经死亡
 * @return 当前生命值小于或等于0时返回true，否则返回false
 */
bool Character::isDead() const {
    return curHealth <= 0;
}

/**
 * 为角色添加一个新的状态效果
 * 状态效果的所有权会被转移给StatusManager
 * @param status 要添加的状态效果
 */
void Character::addStatus(std::unique_ptr<StatusEffect> status) {
    statusManager.addStatus(std::move(status));
}

/**
 * 执行角色自身的回合开始逻辑
 * 子类可以重写该方法以实现玩家或敌人的特殊回合开始行为
 */
void Character::handleTurnStart() {
}

/**
 * 执行角色自身的回合结束逻辑
 * 子类可以重写该方法以实现玩家或敌人的特殊回合结束行为
 */
void Character::handleTurnEnd() {
}

/**
 * 开始角色回合
 * 首先结算回合开始时触发的状态效果，
 * 如果角色仍然存活，再执行角色自身的回合开始逻辑
 */
void Character::beginTurn() {
    statusManager.onTurnStart(*this);

    if (isDead()) {
        return;
    }

    handleTurnStart();
}

/**
 * 结束角色回合
 * 首先执行角色自身的回合结束逻辑，
 * 随后结算回合结束时触发的状态效果
 */
void Character::endTurn() {
    handleTurnEnd();

    statusManager.onTurnEnd(*this);
}

/**
 * 根据角色当前状态计算最终输出伤害
 * @param damage 基础伤害值
 * @return 经过力量、虚弱等状态计算后的输出伤害
 */
int Character::calculateOutgoingDamage(int damage) {
    return statusManager.calculateOutgoingDamage(damage);
}

/**
 * 根据角色当前状态计算最终承受伤害
 * @param damage 攻击者计算完成后的输出伤害
 * @return 经过易伤等状态计算后的最终承受伤害
 */
int Character::calculateIncomingDamage(int damage) {
    return statusManager.calculateIncomingDamage(damage);
}

/**
 * 根据角色当前状态计算最终获得的护盾值
 * @param baseArmor 基础护盾值
 * @return 经过状态效果计算后的最终护盾值
 */
int Character::calculateArmorGain(int baseArmor) {
    return statusManager.calculateArmorGain(baseArmor);
}

/**
 * 获取角色名称
 * @return 角色名称的常量引用
 */
const std::string& Character::getName() const {
    return name;
}

/**
 * 获取角色最大生命值
 * @return 最大生命值
 */
int Character::getMaxHealth() const {
    return maxHealth;
}

/**
 * 获取角色当前生命值
 * @return 当前生命值
 */
int Character::getCurHealth() const {
    return curHealth;
}

/**
 * 获取角色当前护盾值
 * @return 当前护盾值
 */
int Character::getArmor() const {
    return armor;
}

/**
 * 获取角色当前所有状态效果的文本描述
 * @return 用于显示的状态效果文本
 */
std::string Character::getStatusText() const {
    return statusManager.getStatusText();
}