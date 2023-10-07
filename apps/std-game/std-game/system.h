#pragma once
#include "utils.h"

namespace wind {
    namespace stdgame {
        class System {
        public:
            virtual void update(entt::registry& registry) = 0;
        };
    }
}