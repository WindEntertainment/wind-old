#pragma once
#include "utils.h"

namespace wind {
    namespace stdgame {        
        class Prefab {
        private:

            string m_name;
            rapidjson::Value m_value;


            void build(rapidjson::Value& dst, rapidjson::Value& src);
        public:
            rapidjson::Document doc;

            Prefab(const char* json);
            Prefab(rapidjson::Value&);

            entt::entity instance(entt::registry& registry);
        };
    }
}