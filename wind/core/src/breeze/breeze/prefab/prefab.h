#pragma once
#include "../utils.h"

namespace wind {
namespace breeze {
class Prefab {
private:
  string m_name;
  cloudy::Container* m_source;

  void build();

public:
  Prefab(string name, cloudy::Document*);
  ~Prefab();

  entt::entity instance(entt::registry& registry, cloudy::Container* source = nullptr);
};
} // namespace breeze
} // namespace wind