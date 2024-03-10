#pragma once
#include "../utils.h"

namespace wind {
namespace breeze {
struct Transform {
  glm::vec3 position = {0, 0, 0};
  glm::vec3 rotation = {0, 0, 0};
  glm::vec3 scale = {0, 0, 0};
};
} // namespace breeze
} // namespace wind