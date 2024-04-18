#include <cstddef>
#include <cstdint>
#include <map>
#include <renderer/renderer.hpp>
#include <stdexcept>
#include <utility>
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

    m_entityToIndex.insert(std::make_pair(entity, index));
    m_indexToEntity.insert(std::make_pair(index, entity));

    return component;
  }

  void destroyEntity(Entity entity) override {
    if (m_entityToIndex.count(entity) == 0)
      return;

    size_t index = m_entityToIndex[entity];
    m_components.erase(m_components.begin() + index);
    m_entityToIndex.erase(m_entityToIndex.find(entity));
    m_indexToEntity.erase(m_indexToEntity.find(index));
  }

private:
  std::vector<Component> m_components;
  std::map<Entity, size_t> m_entityToIndex;
  std::map<size_t, Entity> m_indexToEntity;
};

template <typename... Components>
class Filter {
public:
};

class World {
public:
  Entity createEntity() {
    if (m_availableIds.empty()) {
      return m_lastEntity++;
    }

    auto entity = m_availableIds.back();
    m_availableIds.pop_back();

    return entity;
  }

  template <typename Component>
  Component attachComponent(Entity entity, Component component) {
    const char* type = typeid(Component).name();

    if (!m_components.count(type))
      m_components.insert(std::make_pair(type, std::make_shared<ComponentPool<Component>>()));

    std::static_pointer_cast<ComponentPool<Component>>(m_components[type])->attachComponent(entity, component);

    return component;
  }

  // const Filter&

private:
  std::vector<Entity> m_availableIds;
  Entity m_lastEntity;

  std::map<const char*, std::shared_ptr<IComponentPool>> m_components;
};

} // namespace wind