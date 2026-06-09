//
// Created by lll on 2026/6/9.
//

#ifndef CARDBATTLE_ENEMYACTION_H
#define CARDBATTLE_ENEMYACTION_H
#include <memory>
#include <string>
#include <vector>

#include "../Effect/Effect.h"

class EnemyAction {
private:
    std::string name;
    std::vector<std::unique_ptr<Effect>> effects;

public:
    explicit EnemyAction(std::string name);

    // 深拷贝，因为 Effect 使用 unique_ptr
    EnemyAction(const EnemyAction& other);

    EnemyAction(EnemyAction&& other) noexcept = default;

    void addEffect(std::unique_ptr<Effect> effect);

    void act(ActionContext& context);

    [[nodiscard]] const std::string& getName() const;
};


#endif //CARDBATTLE_ENEMYACTION_H
