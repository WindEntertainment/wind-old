#pragma once
#include "../resource_manager.h"
#include "../../../breeze/breeze/prefab/prefab.h"

namespace wind {
    namespace resources {
        template<>
        breeze::Prefab* get(const char* name);
    }
}