cmake_minimum_required(VERSION 4.2)
project(CardBattle)

add_executable(CardBattle
        src/main.cpp
        src/Entity/Character.cpp
        src/Entity/Player.cpp
        src/Entity/Enemy.cpp
        src/Card/Card.cpp
        src/Card/Card.h
        src/Game/TurnManager.cpp
        src/Game/Event.h
        src/Game/Battle.cpp
        src/Game/Battle.h
        src/Deck/DeckManager.cpp
        src/Deck/DeckManager.h
        src/Effect/Effect.h
        src/Effect/DamageEffect.h
        src/Effect/GainArmorEffect.h
        src/Entity/StatusEffect/StatusManager.cpp
        src/Entity/StatusEffect/StatusManager.h
        src/Entity/StatusEffect/StatusEffect.cpp
        src/Entity/StatusEffect/StatusEffect.h
        src/Entity/StatusEffect/PoisonStatus.h
        src/Entity/StatusEffect/StrengthStatus.h
        src/Entity/StatusEffect/WeakStatus.h
        src/Entity/StatusEffect/VulnerableStatus.h
        src/Entity/StatusEffect/DexterityStatus.h
        src/Effect/GainStatusEffect.h
        src/Effect/DrawCardEffect.h
        src/Effect/GainEnergyEffect.h
        src/Game/ActionContext.h
        src/Action/EnemyAction.cpp
        src/Action/EnemyAction.h
        src/Game/GameType.h
        src/Effect/Effect.cpp
)

target_compile_options(CardBattle PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
)

set_target_properties(CardBattle PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
