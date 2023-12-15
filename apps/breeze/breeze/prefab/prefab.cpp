#include "prefab.h"
#include "component_registry.h"

#include <resources/resource_manager.h>

namespace wind {
    namespace breeze {
        Prefab::Prefab(string _name, cloudy::Document* _doc):
            m_name(_name) 
        {
            m_source = _doc->root();
            build();
        }

        void Prefab::build() {
            std::function<void(cloudy::Object*, cloudy::Object*)> inheritance =
                [&](cloudy::Object* _parent, cloudy::Object* _child) {
                    if (_parent->getType() != _child->getType())
                        return;

                    if (_parent->isContainer()) { 
                        auto parent = _parent->asContainer();
                        auto child = _child->asContainer();

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


            std::function<void(cloudy::Container*)> recursed = 
                [&](cloudy::Container* _source) {
                    auto baseof = _source->getObject("baseof");
                    if (baseof && baseof->isValue()) {
                        auto name = baseof->asValue()->asString();
                        auto base = resources::get<Prefab>(name.c_str());
                        inheritance(base->m_source, _source);
                    }

                    auto children = _source->getObject("children");
                    if (!children || !children->isContainer())
                        return;

                    for (auto& obj : *children->asContainer())
                        if (obj.second->isContainer())
                            recursed(obj.second->asContainer());
                };

            recursed(m_source);
        }

        entt::entity Prefab::instance(entt::registry& registry, cloudy::Container* source) {
            if (!source)
                source = m_source;

            auto entity = registry.create();

            auto components = source->getObject("components");
            if (components && components->isContainer())
                for (auto& component : *components->asContainer())
                    if (component.second->isContainer())
                        ComponentRegistry::build(
                            registry, entity,
                            component.first, component.second->asContainer()
                        );
            
            auto children = source->getObject("children");
            if (children && children->isContainer())
                for (auto& obj : *children->asContainer())
                    if (obj.second->isContainer())
                        instance(registry, obj.second->asContainer());


            return entity;
        }
    }
}