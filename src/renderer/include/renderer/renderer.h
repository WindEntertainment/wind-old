#pragma once
#include <utils/utils.h>

namespace wind {
class Renderer {
public:
    static void setOrtho(ivec2 size);
    static void clear(ivec4 color);

    static void drawRectangle(vec4 rect, vec4 color);
    static void drawCircle(vec2 center, float radius, vec4 color);
};

} // namespace wind