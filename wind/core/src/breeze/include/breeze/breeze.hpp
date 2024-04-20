#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace wind {

using Entity = std::uint8_t;

class IComponentPool {
public:
  virtual void destroyEntity(Entity) = 0;
  virtual bool hasEntity(Entity) = 0;
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

  bool hasEntity(Entity entity) override {
    return m_entityToIndex.count(entity);
  }

  Component& getByEntity(Entity entity) {
    if (!m_entityToIndex.count(entity))
      throw std::invalid_argument("ComponentPool doesn't have an entity");

    return m_components[m_entityToIndex[entity]];
  }

private:
  std::vector<Component> m_components;
  std::map<Entity, size_t> m_entityToIndex;
  std::map<size_t, Entity> m_indexToEntity;
};

class World {
public:
  Entity createEntity() {
    Entity newEntity;

    if (m_availableIds.empty()) {
      newEntity = m_lastEntity++;
    } else {
      newEntity = m_availableIds.back();
      m_availableIds.pop_back();
    }

    m_entities.push_back(newEntity);

    return newEntity;
  }

  template <typename Component>
  Component attachComponent(Entity entity, Component component) {
    const char* type = typeid(Component).name();

    if (!m_components.count(type))
      m_components.insert(std::make_pair(type, std::make_shared<ComponentPool<Component>>()));

    std::static_pointer_cast<ComponentPool<Component>>(m_components[type])->attachComponent(entity, component);

    return component;
  }

  template <typename Component>
  bool hasComponent(Entity entity) {
    const char* type = typeid(Component).name();

    if (!m_components.count(type))
      return false;

    return m_components[type]->hasEntity(entity);
  }

  template <typename Component>
  Component& getComponent(Entity entity) {
    const char* type = typeid(Component).name();

    if (!m_components.count(type))
      return false;

    return std::static_pointer_cast<ComponentPool<Component>>(m_components[type])->getByEntity(entity);
  }

  template <typename Func>
  void forEach(Func function) {
    for (const auto& entity : m_entities)
      function(entity);
  }

  template <typename... Components, typename Func>
  void forEach(Func function) {
    for (const auto& entity : m_entities)
      if ((m_components[typeid(Components).name()]->hasEntity(entity) && ...))
        function(entity, std::static_pointer_cast<ComponentPool<Components>>(m_components[typeid(Components).name()])->getByEntity(entity)...);
  }

  template <typename... Components, typename Func>
  void forEachWith(Func function) {
    for (const auto& entity : m_entities)
      if ((m_components[typeid(Components).name()]->hasEntity(entity) && ...))
        function(std::static_pointer_cast<ComponentPool<Components>>(m_components[typeid(Components).name()])->getByEntity(entity)...);
  }

private:
  std::vector<Entity> m_entities;
  std::vector<Entity> m_availableIds;
  Entity m_lastEntity;

  std::map<const char*, std::shared_ptr<IComponentPool>> m_components;
};

} // namespace wind