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

class IFilter {};

template <typename... Components>
class Filter : public IFilter {
private:
  std::vector<std::tuple<Components&...>> m_components;
  std::vector<Entity> m_entities;

public:
  void addEntity(Entity entity, std::tuple<Components&...> components) {
    m_entities.push_back(entity);
    m_components.push_back(components);
  }

  auto begin() {
    return m_components.begin();
  }

  auto end() {
    return m_components.end();
  }
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

  // template <typename... Components>
  // auto createFilter() {
  //   auto filter = std::make_shared<Filter<Components...>>();

  //   std::vector<const char*> types;
  //   (types.push_back(typeid(Components).name()), ...);

  //   for (const char* type : types)
  //     m_filters.insert(std::make_pair(type, filter));

  //   for (const auto& entity : m_entities) {
  //     bool valid = true;
  //     for (const auto& type : types)
  //       if (!m_components[type]->hasEntity(entity)) {
  //         valid = false;
  //         break;
  //       }

  //     if (!valid)
  //       continue;

  //     // std::tuple<Components...> components;
  //     auto components = std::make_tuple();
  //     // (components = std::tuple_cat(components, std::make_tuple(std::static_pointer_cast<ComponentPool<Components>>(m_components[typeid(Components).name()])->getByEntity(entity))), ...);

  //     // ((modifedTuple(std::make_tuple(std::static_pointer_cast<ComponentPool<Components>>(m_components[typeid(Components).name()])->getByEntity(entity))))), ...);

  //     filter->addEntity(entity, components);
  //   }

  //   return filter;
  // }

  template <typename... Components>
  auto createFilter() {
    auto filter = std::make_shared<Filter<Components...>>();

    std::vector<const char*> types;
    ((types.push_back(typeid(Components).name())), ...);

    for (const char* type : types)
      m_filters.insert(std::make_pair(type, filter));

    for (const auto& entity : m_entities) {
      bool valid = true;
      for (const auto& type : types)
        if (!m_components[type]->hasEntity(entity)) {
          valid = false;
          break;
        }

      if (!valid)
        continue;

      std::tuple<Components*...> components;
      std::apply([&](auto&... args) {
        ((args = &(std::static_pointer_cast<ComponentPool<Components>>(m_components[typeid(Components).name()])->getByEntity(entity))), ...);
      },
        components);

      auto n = std::tuple<Components&...>(*std::get<Components*>(components)...);

      filter->addEntity(entity, n);
    }

    return filter;
  }

private:
  std::vector<Entity> m_entities;
  std::vector<Entity> m_availableIds;
  Entity m_lastEntity;

  std::map<const char*, std::shared_ptr<IComponentPool>> m_components;
  std::map<const char*, std::shared_ptr<IFilter>> m_filters;
};

} // namespace wind