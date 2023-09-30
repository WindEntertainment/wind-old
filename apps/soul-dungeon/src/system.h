#pragma once
#include "game.h"

namespace soul_dungeon {
    class System {
    public:
        virtual void update(entt::registry& registry) = 0;
    };
}