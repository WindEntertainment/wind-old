#include "prefab.h"
#include "component_registry.h"

#include <resources/resource_manager.h>

namespace wind {
    namespace stdgame {
        Prefab::Prefab(const char* json) {
            doc.Parse(json);
            
            if (!doc.IsObject())
                throw std::invalid_argument("root element of prefab must be object");

            build(doc.GetObject());
        };

        Prefab::Prefab(rapidjson::GenericObject<false, rapidjson::Value> object) {
            build(object);
        }

        void Prefab::build(rapidjson::GenericObject<false, rapidjson::Value> object) {
            if (object.HasMember("base"))
                object = resources::get<Prefab>(object["base"].GetString())->doc.GetObject();

            if (!object.HasMember("components"))
                throw std::invalid_argument("Miss 'components' field");

            if (!object["components"].IsObject())
                throw std::invalid_argument("'components' field must be array");

            for (auto& component : object["components"].GetObject()) {
                if (!component.name.IsString())
                    throw std::invalid_argument("'component.name' must be string");

                if (!component.value.IsObject())
                    throw std::invalid_argument("'component.value' must be object");
            }
        }

        entt::entity Prefab::instance(entt::registry& registry, rapidjson::GenericObject<false, rapidjson::Value> object) {
            if (object.HasMember("base"))
                object = resources::get<Prefab>(object["base"].GetString())->doc.GetObject();
            
            auto obj = registry.create();

            for (auto& component : object["components"].GetObject())
                ComponentRegistry::build(
                    registry, obj,
                    component.name.GetString(), component.value.GetObject()
                );

            if (object.HasMember("children") && object["children"].IsArray()) {
                for (auto& child : object["children"].GetArray()) {
                    if (!child.IsObject())
                        continue;;
                    auto child_obj = child.GetObject();

                    Prefab temp(child_obj);
                    temp.instance(registry, child_obj);
                }
            }

            return obj;
        }

        entt::entity Prefab::instance(entt::registry& registry) {
            if (!doc.IsObject()) {
                log().error() << "Can't instantinate incomplete prefab";
                return entt::null;
            }

            return instance(registry, doc.GetObject());
        }
    }
}