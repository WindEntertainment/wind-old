#include <cstddef>
#include <cstdint>
#include <map>
#include <renderer/renderer.hpp>
#include <stdexcept>
#include <utility>
#include <vcruntime.h>
#include <vector>

namespace wind {

using Entity = std::uint8_t;


class IComponentPool {
public:
    virtual void destroyEntity(Entity) = 0;  
};

template <typename Component>
class ComponentPool final : public IComponentPool {
public:
    Component& attachComponent(const Entity& entity, Component& component) noexcept {
        size_t index = m_components.size();
        m_components.push_back(component);

        m_entity_to_index.insert(std::make_pair(entity, index));
        m_index_to_entity.insert(std::make_pair(index, entity));
    
        return component;
    }

    void destroyEntity(Entity entity) override {
        if (m_entity_to_index.count(entity) == 0)
            return;

        size_t index = m_entity_to_index[entity];
        m_components.erase(m_components.begin() + index);
        m_entity_to_index.erase(m_entity_to_index.find(entity));
        m_index_to_entity.erase(m_index_to_entity.find(index));
    }
private:
    std::vector<Component> m_components;
    std::map<Entity, size_t> m_entity_to_index;
    std::map<size_t, Entity> m_index_to_entity; 
};


class World {
public:
    Entity createEntity() {
        if (m_aviables.empty()) {
            return m_last_entity++;
        } 

        auto entity = m_aviables.back();
        m_aviables.pop_back();

        return entity;
    }

    template<typename Component> 
    Component attachComponent(Entity entity, Component component) {
        const char* type = typeid(Component).name();

        if (!m_components.count(type))
            m_components.insert(std::make_pair(type, ComponentPool<Component>()));

        static_cast<ComponentPool<Component>>(m_components[type]).attachComponent(entity, component);
    }
private:
    std::vector<Entity> m_aviables;
    Entity m_last_entity;

    std::map<const char*, IComponentPool> m_components;
};

} // namespace wind