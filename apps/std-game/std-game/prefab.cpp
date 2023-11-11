#include "prefab.h"
#include "component_registry.h"

#include <resources/resource_manager.h>

namespace wind {
    namespace stdgame {
       /* void test(rapidjson::Document& doc) {
            std::function<void(rapidjson::Value&, rapidjson::Value& )> inheritance =
                [&](rapidjson::Value& _child, rapidjson::Value& _parent) {
                    if (_parent.GetType() != _child.GetType()) 
                        return;

                    if (_parent.IsObject()) {
                        auto parent = _parent.GetObject();
                        auto child = _child.GetObject();

                        if (parent.HasMember("base"))
                            inheritance(parent, resources::get<Prefab>(parent["base"].GetString())->doc);

                        for (auto& value : parent) {
                            for (auto& cvalue : child) {
                                log().debug() << cvalue.name.GetString();
                            }

                            if (child.HasMember(value.name)) {
                                if (child.HasMember(value.name) && value.name.GetStringLength() == 8)
                                    inheritance(child[value.name], value.value);
                            }
                            else
                                child.AddMember(value.name, value.value, doc.GetAllocator());
                        } 
                    }

                    if (_parent.IsArray()) {
                        auto parent = _parent.GetArray();
                        auto child = _child.GetArray();

                        auto overall = std::min(parent.Size(), child.Size());

                        for (auto i = 0U; i < overall; ++i)
                            inheritance(parent[i], child[i]);
                    }                    
                };

            inheritance(doc, doc);
            print(doc);
        }*/

        Prefab::Prefab(string _name, dom::Document* _doc) {
            m_name = _name;
            m_source = _doc->root();
            build();
        }

        Prefab::Prefab(string _name, dom::Container* _src) {
            m_name = _name;
            m_source = _src;
            build();
        }

        void Prefab::build() {
            
        }

        entt::entity Prefab::instance(entt::registry& registry) {
            auto entity = registry.create();

            auto components = m_source->getObject("components");
            if (components && components->isContainer())
                for (auto& component : *(dom::Container*)components) {
                    if (component.second->isContainer())
                        ComponentRegistry::build(
                            registry, entity,
                            component.first, (dom::Container*)component.second
                        );
                }
            
            /*if (object.HasMember("children") && object["children"].IsArray()) {
                for (auto& child : object["children"].GetArray()) {
                    if (!child.IsObject())
                        continue;

                    Prefab temp(child);
                    temp.instance(registry);
                }
            }*/

            return entity;
        }
    }
}