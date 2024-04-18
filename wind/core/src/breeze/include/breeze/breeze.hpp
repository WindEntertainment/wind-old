#include <renderer/renderer.hpp>

namespace wind {

using Entity = unsigned int;

class World {
private:
  std::vector<Entity> m_entities;
  std::map<Entity, std::vector<void*>> m_components;

  Entity last_index = 0;

public:
  template <typename T>
  T* addComponent(Entity entity, T component) {
    m_components[entity].push_back(component);
  }

  Entity createEntity() {
    m_entities.push_back(last_index++);
    return m_entities.back();
  }
};

} // namespace wind