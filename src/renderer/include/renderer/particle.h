#pragma once
#include <utils/utils.h>

namespace wind {

struct Particle {
public:
    vec2 position;
    vec2 rotation;
    vec2 scale;

private:
    uint m_VAO, m_VBO;
};

} // namespace wind