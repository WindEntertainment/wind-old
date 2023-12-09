#include "prefab.h"
#include "component_registry.h"

#include <resources/resource_manager.h>

namespace wind {
    namespace stdgame {
        Prefab::Prefab(string _name, doom::Document* _doc) {
            m_name = _name;
            m_source = _doc->root();
            build();
        }

        void Prefab::build() {
            std::function<void(doom::Object*, doom::Object*)> inheritance =
                [&](doom::Object* _parent, doom::Object* _child) {
                    if (_parent->getType() != _child->getType())
                        return;

                    if (_parent->isContainer()) {
                        auto parent = (doom::Container*)_parent;
                        auto child = (doom::Container*)_child;

                        for (auto& value : *parent) {
                            if (child->hasMember(value.first))
                                inheritance(value.second, child->getObject(value.first));
                            else 
                                child->addObject(value.first, value.second);
                        }
                    }
                };

            auto baseof = m_source->getObject("baseof");
            if (baseof && baseof->isValue()) {
                auto base = resources::get<Prefab>(((doom::Value*)baseof)->asString().c_str());
                inheritance(base->m_source, m_source);
            }

            auto children = m_source->getObject("children");
            if (!children || !children->isContainer())
                return;

            for (auto& obj : *(doom::Container*)children) {
                if (obj.second->isContainer()) {
                    auto child = (doom::Container*)obj.second;
                    if (child->hasMember("baseof")) {
                        auto baseof = child->getObject("baseof");
                        if (baseof && baseof->isValue()) {
                            auto base = resources::get<Prefab>(((doom::Value*)baseof)->asString().c_str());
                            inheritance(base->m_source, obj.second);
                        }
                    }
                }
            }
                
        }

        entt::entity Prefab::instance(entt::registry& registry, doom::Container* source) {
            if (!source)
                source = m_source;

            auto entity = registry.create();

            auto components = source->getObject("components");
            if (components && components->isContainer())
                for (auto& component : *(doom::Container*)components)
                    if (component.second->isContainer())
                        ComponentRegistry::build(
                            registry, entity,
                            component.first, (doom::Container*)component.second
                        );
            
            auto children = source->getObject("children");
            if (children && children->isContainer())
                for (auto& obj : *(doom::Container*)children)
                    if (obj.second->isContainer())
                        instance(registry, (doom::Container*)obj.second);


            return entity;
        }
    }
}