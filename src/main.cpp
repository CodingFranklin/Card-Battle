#ifdef _WIN32
#include <windows.h>
#endif

#include <clocale>
#include <iostream>

#include "Effect/DamageEffect.h"
#include "Effect/GainArmorEffect.h"
#include "Effect/GainStatusEffect.h"
#include "Entity/Character.h"
#include "Entity/StatusEffect/PoisonStatus.h"
#include "Entity/StatusEffect/StrengthStatus.h"
#include "Game/Battle.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main() {
// 让console能够解码输出中文
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::setlocale(LC_ALL, ".UTF-8");


    Player player("诗人", 80.0f, 3);

    if (!player.deckManager.initializeFromJson("cards.json", "starter_deck.json")) {
        std::cerr << "Failed to initialize player deck from JSON files." << std::endl;
        return 1;
    }

    Enemy slime("蟑螂", 15.0f, 6.0f);
    Enemy dragon("恶魔", 75.0f, 15.0f);

    EnemyAction attack_1("Attack 6 and block 4");
    attack_1.addEffect(std::make_unique<DamageEffect>(6,TargetType::Single));
    attack_1.addEffect(std::make_unique<GainArmorEffect>(4,TargetType::Self));

    EnemyAction attack_2("Poison 3");
    attack_2.addEffect(std::make_unique<GainStatusEffect>(std::make_unique<PoisonStatus>(3), TargetType::Single));

    EnemyAction strength("Gain 1 Strength");
    strength.addEffect(std::make_unique<GainStatusEffect>(std::make_unique<StrengthStatus>(1), TargetType::Self));

    EnemyAction normal_attack("Attack 5");
    normal_attack.addEffect(std::make_unique<DamageEffect>(5,TargetType::Single));

    slime.addAction(normal_attack);
    slime.addAction(attack_1);
    slime.addAction(attack_2);

    dragon.addAction(strength);
    dragon.addAction(normal_attack);
    dragon.addAction(normal_attack);

    std::vector<Enemy*> enemies = { &slime, &dragon };

    Battle battle(player, enemies);

    battle.start();

    return 0;
}