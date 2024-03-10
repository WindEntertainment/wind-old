#pragma once
#include "../utils.h"

namespace wind {
namespace breeze {
struct Renderable {
  renderer::Mesh* mesh;
  renderer::Texture* texture;
  renderer::Shader* shader;
  glm::vec2 tiling;
};

} // namespace breeze
} // namespace wind