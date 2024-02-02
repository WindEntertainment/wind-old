#pragma once
#include "renderer/particle.h"
#include <utils/utils.h>

namespace wind {

static float m_scope = 1.f;
static ivec2 m_projectionPortSize = vec2();
static glm::mat4 m_orthoMatrix = glm::mat4(1);
static glm::mat4 m_viewMatrix = glm::mat4(1);

class Renderer {
public:
    static void setOrtho(ivec2 size, float scope = 1.f);
    static void clear(vec4 color);

    static void updateCamera(vec2 position);
    static void setScope(float scope);
    static void drawRectangle(vec4 rect, vec4 color);
    static void drawCircle(vec2 center, float radius, vec4 color);
    static void drawParticles(ParticleSystem* particles);
};

} // namespace wind