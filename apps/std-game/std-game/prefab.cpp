#include "prefab.h"
#include "component_registry.h"

#include <resources/resource_manager.h>

namespace wind {
    namespace stdgame {
        Prefab::Prefab(string _name, cloudy::Document* _doc) {
            m_name = _name;
            m_source = _doc->root();
            build();
        }

        void Prefab::build() {
            std::function<void(cloudy::Object*, cloudy::Object*)> inheritance =
                [&](cloudy::Object* _parent, cloudy::Object* _child) {
                    if (_parent->getType() != _child->getType())
                        return;

                    if (_parent->isContainer()) {
                        auto parent = (cloudy::Container*)_parent;
                        auto child = (cloudy::Container*)_child;

                        for (auto& value : *parent) {
                            if (child->hasMember(value.first))
                                inheritance(value.second, child->getObject(value.first));
                            else {
                                auto allocator = _child->allocator();
                                child->addObject(value.first, value.second->copy(allocator));
                            }
                        }
                    }
                };

            auto baseof = m_source->getObject("baseof");
            if (baseof && baseof->isValue()) {
                auto base = resources::get<Prefab>(((cloudy::Value*)baseof)->asString().c_str());
                inheritance(base->m_source, m_source);
            }

            auto children = m_source->getObject("children");
            if (!children || !children->isContainer())
                return;

            for (auto& obj : *(cloudy::Container*)children) {
                if (obj.second->isContainer()) {
                    auto child = (cloudy::Container*)obj.second;
                    if (child->hasMember("baseof")) {
                        auto baseof = child->getObject("baseof");
                        if (baseof && baseof->isValue()) {
                            auto base = resources::get<Prefab>(((cloudy::Value*)baseof)->asString().c_str());
                            inheritance(base->m_source, obj.second);
                        }
                    }
                }
            }
                
        }

        entt::entity Prefab::instance(entt::registry& registry, cloudy::Container* source) {
            if (!source)
                source = m_source;

            auto entity = registry.create();

            auto components = source->getObject("components");
            if (components && components->isContainer())
                for (auto& component : *(cloudy::Container*)components)
                    if (component.second->isContainer())
                        ComponentRegistry::build(
                            registry, entity,
                            component.first, (cloudy::Container*)component.second
                        );
            
            auto children = source->getObject("children");
            if (children && children->isContainer())
                for (auto& obj : *(cloudy::Container*)children)
                    if (obj.second->isContainer())
                        instance(registry, (cloudy::Container*)obj.second);


            return entity;
        }
    }
}