#pragma once
#include <utils/utils.h>

namespace wind {
class Renderer {
public:
    static void setOrtho(ivec2 size, float scope = 1.f);
    static void clear(vec4 color);

    static void updateCamera(vec2 position);
    static void setScope(float scope);
    static void drawRectangle(vec4 rect, vec4 color);
    static void drawCircle(vec2 center, float radius, vec4 color);
};

} // namespace wind