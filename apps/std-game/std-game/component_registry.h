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
                        cloudy::Container*
                    )
                >
            > builders;
        public:
            static void addComponent(
                string name,
                std::function<void(
                    entt::registry&, entt::entity,
                    cloudy::Container*
                )> func
            );

            static void build(
                entt::registry& registry,
                entt::entity entity,
                string component,
                cloudy::Container* object
            );

            static void init();
        };
    }
}