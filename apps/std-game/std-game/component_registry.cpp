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
                    dom::Container*
                )
            >
        > ComponentRegistry::builders;

        void ComponentRegistry::addComponent(
            string name,
            std::function<void(
                entt::registry&, entt::entity,
                dom::Container*
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
            dom::Container* object
        ) {
            if (!builders.contains(component)) {
                log().error() << "ComponentRegistry: failed build component: [" << component << "]";
                return;
            }

            builders[component](registry, entity, object);
        }

        void ComponentRegistry::init() {
            addComponent("stdgame.transform",
                [](entt::registry& registry, entt::entity entity, dom::Container* dom) {
                    Transform transform;

                    auto position = dom->getObject("position");
                    if (position && position->isContainer()) {
                        auto pos = (dom::Container*)position;
                        
                        auto x = pos->getObject("x");
                        auto y = pos->getObject("y");
                        auto z = pos->getObject("z");

                        if (x && x->isValue()) transform.position.x = ((dom::Value*)x)->asFloat();
                        if (y && y->isValue()) transform.position.y = ((dom::Value*)y)->asFloat();
                        if (z && z->isValue()) transform.position.z = ((dom::Value*)z)->asFloat();
                    }

                    auto rotation = dom->getObject("rotation");
                    if (rotation && rotation->isContainer()) {
                        auto rot = (dom::Container*)rotation;
                        
                        auto x = rot->getObject("x");
                        auto y = rot->getObject("y");
                        auto z = rot->getObject("z");

                        if (x && x->isValue()) transform.rotation.x = ((dom::Value*)x)->asFloat();
                        if (y && y->isValue()) transform.rotation.y = ((dom::Value*)y)->asFloat();
                        if (z && z->isValue()) transform.rotation.z = ((dom::Value*)z)->asFloat();
                    }

                    auto scale = dom->getObject("scale");
                    if (rotation && rotation->isContainer()) {
                        auto scl = (dom::Container*)scale;
                        
                        auto x = scl->getObject("x");
                        auto y = scl->getObject("y");
                        auto z = scl->getObject("z");

                        if (x && x->isValue()) transform.scale.x = ((dom::Value*)x)->asFloat();
                        if (y && y->isValue()) transform.scale.y = ((dom::Value*)y)->asFloat();
                        if (z && z->isValue()) transform.scale.z = ((dom::Value*)z)->asFloat();
                    }

                    registry.emplace_or_replace<Transform>(entity, transform);
                }
            );

            addComponent("stdgame.renderable",
                [](entt::registry& registry, entt::entity entity, dom::Container* dom) {
                    auto mesh = dom->getObject("mesh");
                    if (!mesh || !mesh->isValue()) {
                        log().error() << "stdgame.renderable must have string mesh field";
                        return;
                    }

                    auto texture = dom->getObject("texture");
                    if (!texture || !texture->isValue()) {
                        log().error() << "stdgame.renderable must have string texture field";
                        return;
                    }

                    auto shader = dom->getObject("shader");
                    if (!shader || !shader->isValue()) {
                        log().error() << "stdgame.renderable must have shader texture field";
                        return;
                    }

                    auto rmesh = resources::get<renderer::Mesh>(((dom::Value*)mesh)->asString().c_str());
                    auto rtexture = resources::get<renderer::Texture>(((dom::Value*)texture)->asString().c_str());
                    auto rshader = resources::get<renderer::Shader>(((dom::Value*)shader)->asString().c_str());

                    registry.emplace_or_replace<Renderable>(entity, rmesh, rtexture, rshader);
                }
            );
        }
    }
}