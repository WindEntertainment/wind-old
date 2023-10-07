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
                        transform.position.x = json["position"].GetArray()[0].GetFloat();
                        transform.position.y = json["position"].GetArray()[1].GetFloat();
                        transform.position.z = json["position"].GetArray()[2].GetFloat();
                    }

                    if (json.HasMember("rotation") && json["rotation"].IsArray()) {
                        transform.rotation.x = json["rotation"].GetArray()[0].GetFloat();
                        transform.rotation.y = json["rotation"].GetArray()[1].GetFloat();
                        transform.rotation.z = json["rotation"].GetArray()[2].GetFloat();
                    }
                    
                    if (json.HasMember("scale") && json["scale"].IsArray()) {
                        transform.scale.x = json["scale"].GetArray()[0].GetFloat();
                        transform.scale.y = json["scale"].GetArray()[1].GetFloat();
                        transform.scale.z = json["scale"].GetArray()[2].GetFloat();
                    }

                    registry.emplace<Transform>(entity, transform);
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

                    mesh->m_texture = texture;
                    mesh->m_shader = shader; 

                    registry.emplace<Renderable>(entity, mesh);
                }
            );
        }
    }
}