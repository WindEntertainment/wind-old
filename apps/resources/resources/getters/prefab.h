#pragma once
#include "../resource_manager.h"
#include "../../../std-game/std-game/prefab.h"

namespace wind {
    namespace resources {
        template<>
        stdgame::Prefab* get(const char* name);
    }
}