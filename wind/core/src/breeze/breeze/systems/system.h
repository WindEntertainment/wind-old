#pragma once
#include "../utils.h"

namespace wind {
namespace breeze {
class System {
public:
  virtual void update(entt::registry& registry) = 0;
};
} // namespace breeze
} // namespace wind