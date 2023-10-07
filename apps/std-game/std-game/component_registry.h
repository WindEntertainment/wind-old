#pragma once
#include "utils.h"

namespace wind {
    namespace stdgame {
        class ComponentRegistry {
        private:
            static map<
                string, std::function<
                    void(
                        entt::registry&, entt::entity,
                        rapidjson::GenericObject<false, rapidjson::Value>
                    )
                >
            > builders;
        public:
            static void addComponent(
                string name,
                std::function<void(
                    entt::registry&, entt::entity,
                    rapidjson::GenericObject<false, rapidjson::Value>
                )> func
            );

            static void build(
                entt::registry& registry,
                entt::entity entity,
                string component,
                rapidjson::GenericObject<false, rapidjson::Value> object
            );

            static void init();
        };
    }
}