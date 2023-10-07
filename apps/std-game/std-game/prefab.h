#pragma once
#include "utils.h"

namespace wind {
    namespace stdgame {        
        class Prefab {
        private:
            rapidjson::Document doc;
        public:
            Prefab(const char* json);
            entt::entity instance(entt::registry& registry);
        };
    }
}