#pragma once
#include "renderer/particle.hpp"
#include "renderer/texture.hpp"

namespace wind {

static float m_scope = 1.f;
static glm::ivec2 m_projectionPortSize = glm::vec2();
static glm::mat4 m_orthoMatrix = glm::mat4(1);
static glm::mat4 m_viewMatrix = glm::mat4(1);

class Renderer {
public:
  static void setOrtho(glm::ivec2 size, float scope = 1.f);
  static void clear(glm::vec4 color);

  static void updateCamera(glm::vec2 position);
  static void setScope(float scope);
  static void drawRectangle(glm::vec4 rect, glm::vec4 color);
  static void drawTexture(Texture* texture, glm::vec2 tiling, glm::vec3 position,
    glm::vec3 rotation, glm::vec2 scale);
  static void drawCircle(glm::vec2 center, float radius, glm::vec4 color);
  static void drawParticles(ParticleSystem* particles);
};

} // namespace wind
