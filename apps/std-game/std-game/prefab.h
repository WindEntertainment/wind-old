#pragma once
#include "utils.h"

namespace wind {
    namespace stdgame {        
        class Prefab {
        private:
            rapidjson::Document doc;

            Prefab(rapidjson::GenericObject<false, rapidjson::Value>);
            void build(rapidjson::GenericObject<false, rapidjson::Value>);
            entt::entity instance(entt::registry& registry, rapidjson::GenericObject<false, rapidjson::Value>);
        public:
            Prefab(const char* json);
            entt::entity instance(entt::registry& registry);
        };
    }
}