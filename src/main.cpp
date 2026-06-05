#ifdef _WIN32
#include <windows.h>
#endif

#include <clocale>
#include <iostream>
#include "Entity/Character.h"
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

    Enemy slime("蟑螂", 15.0f, 6.0f);
    Enemy dragon("恶魔", 75.0f, 10.0f);

    std::vector<Enemy*> enemies = { &slime, &dragon };

    Battle battle(player, enemies);

    battle.start();

    return 0;
}