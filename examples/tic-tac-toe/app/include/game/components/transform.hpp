#pragma once
#include <glm/glm.hpp>

namespace game {

struct Transform {
  glm::vec3 position = {};
  glm::vec2 rotation = {};
  glm::vec2 scale = {1, 1};
};

} // namespace game