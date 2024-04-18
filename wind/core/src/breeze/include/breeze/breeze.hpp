#include <cstddef>
#include <cstdint>
#include <map>
#include <renderer/renderer.hpp>
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


class ECS {

};

} // namespace wind