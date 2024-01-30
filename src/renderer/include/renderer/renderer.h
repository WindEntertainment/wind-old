#pragma once
#include "camera.h"
#include "mesh.h"

namespace wind {
namespace renderer {

class Renderer {
public:
    void clear();
    void render(Camera *, Mesh *, Texture *, vec2 tiling, Shader *,
                vec3 position, vec3 rotation, vec3 scale);
};

} // namespace renderer
} // namespace wind