#include "prefab.h"
#include "component_registry.h"

#include <resources/resource_manager.h>

namespace wind {
    namespace stdgame {
        void print(rapidjson::Value& value) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            value.Accept(writer);
            log().debug() << buffer.GetString();
        }

        void test(rapidjson::Document& doc) {
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
        }

        Prefab::Prefab(const char* json) {
            doc.Parse(json);
            if (!doc.IsObject())
                throw std::invalid_argument("node element of prefab must be object");
            
            test(doc);
            m_value = doc.GetObject();
        };

        Prefab::Prefab(rapidjson::Value& src) {
            m_value = src.GetObject();
          //  build(m_value, src);
        }

        void Prefab::build(rapidjson::Value& dst, rapidjson::Value& src) {
           /* dst.SetObject();
            auto object = src.GetObject();

            if (object.HasMember("base") && object["base"].IsString()) {
              //  auto& child = resources::get<Prefab>(object["base"].GetString())->m_value;
              //  build(dst, child);
            }


            //if (object.HasMember("components") && object["components"].IsObject())
            //    for (auto& field : object["components"].GetObject())*/
                    
        }

        entt::entity Prefab::instance(entt::registry& registry) {
          /*  auto& object = m_value;

            auto entity = registry.create();

            log().debug() << "instance:";
            print(object);
            if (object.HasMember("components") && object["components"].IsObject())
                for (auto& component : object["components"].GetObject()) {
                    ComponentRegistry::build(
                        registry, entity,
                        component.name.GetString(), component.value.GetObject()
                    );
                }
            
            if (object.HasMember("children") && object["children"].IsArray()) {
                for (auto& child : object["children"].GetArray()) {
                    if (!child.IsObject())
                        continue;

                    Prefab temp(child);
                    temp.instance(registry);
                }
            }

            return entity;*/
        }
    }
}