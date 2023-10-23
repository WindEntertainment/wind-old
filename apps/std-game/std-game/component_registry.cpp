#include "component_registry.h"

#include "transform.h"
#include "renderable.h"

#include <resources/resource_manager.h>

namespace wind {
    namespace stdgame {
         map<
            string, std::function<
                void(
                    entt::registry&, entt::entity,
                    rapidjson::GenericObject<false, rapidjson::Value>
                )
            >
        > ComponentRegistry::builders;

        void ComponentRegistry::addComponent(
            string name,
            std::function<void(
                entt::registry&, entt::entity,
                rapidjson::GenericObject<false, rapidjson::Value>
            )> func
        ) {
            builders.insert(std::make_pair(
                name, func
            ));
        }

        void ComponentRegistry::build(
            entt::registry& registry,
            entt::entity entity,
            string component,
            rapidjson::GenericObject<false, rapidjson::Value> object
        ) {
            if (!builders.contains(component)) {
                log().error() << "ComponentRegistry: failed build component: [" << component << "]";
                return;
            }

            builders[component](registry, entity, object);
        }

        void ComponentRegistry::init() {
            using JObject = rapidjson::GenericObject<false, rapidjson::Value>;

            addComponent("stdgame.transform",
                [](entt::registry& registry, entt::entity entity, JObject json) {
                    Transform transform;

                    if (json.HasMember("position") && json["position"].IsArray()) {
                        auto pos = json["position"].GetArray();
                        if (pos.Size() > 0) transform.position.x = pos[0].GetFloat();
                        if (pos.Size() > 1) transform.position.y = pos[1].GetFloat();
                        if (pos.Size() > 2) transform.position.z = pos[2].GetFloat();
                    }

                    if (json.HasMember("rotation") && json["rotation"].IsArray()) {
                        auto rot = json["rotation"].GetArray();
                        if (rot.Size() > 0) transform.rotation.x = rot[0].GetFloat();
                        if (rot.Size() > 1) transform.rotation.y = rot[1].GetFloat();
                        if (rot.Size() > 2) transform.rotation.z = rot[2].GetFloat();
                    }
                    
                    if (json.HasMember("scale") && json["scale"].IsArray()) {
                        auto scl = json["scale"].GetArray();
                        if (scl.Size() > 0) transform.scale.x = scl[0].GetFloat();
                        if (scl.Size() > 1) transform.scale.y = scl[1].GetFloat();
                        if (scl.Size() > 2) transform.scale.z = scl[2].GetFloat();
                    }

                    registry.emplace_or_replace<Transform>(entity, transform);
                }
            );

            addComponent("stdgame.renderable",
                [](entt::registry& registry, entt::entity entity, JObject json) {
                    if (!json.HasMember("mesh") || !json["mesh"].IsString()) {
                        log().error() << "stdgame.renderable must have string mesh field";
                        return;
                    }

                    if (!json.HasMember("texture") || !json["texture"].IsString()) {
                        log().error() << "stdgame.renderable must have string texture field";
                        return;
                    }

                    if (!json.HasMember("shader") || !json["shader"].IsString()) {
                        log().error() << "stdgame.renderable must have shader texture field";
                        return;
                    }

                    auto mesh = resources::get<renderer::Mesh>(json["mesh"].GetString());
                    auto texture = resources::get<renderer::Texture>(json["texture"].GetString());
                    auto shader = resources::get<renderer::Shader>(json["shader"].GetString());

                    registry.emplace_or_replace<Renderable>(entity, mesh, texture, shader);
                }
            );
        }
    }
}