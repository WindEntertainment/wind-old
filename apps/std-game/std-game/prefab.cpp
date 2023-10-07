#include "prefab.h"
#include "component_registry.h"

namespace wind {
    namespace stdgame {
        Prefab::Prefab(const char* json) {
            doc.Parse(json);
            
            if (!doc.HasMember("components"))
                throw std::invalid_argument("Miss 'components' field");

            if (!doc["components"].IsObject())
                throw std::invalid_argument("'components' field must be array");

            for (auto& component : doc["components"].GetObject()) {
                if (!component.name.IsString())
                    throw std::invalid_argument("'component.name' must be string");

                if (!component.value.IsObject())
                    throw std::invalid_argument("'component.value' must be object");
            }
        };

        entt::entity Prefab::instance(entt::registry& registry) {
            auto obj = registry.create();

            for (auto& component : doc["components"].GetObject())
                ComponentRegistry::build(
                    registry, obj,
                    component.name.GetString(), component.value.GetObject()
                );

            return obj;
        };
    }
}