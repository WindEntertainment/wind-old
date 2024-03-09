#pragma once
#include <renderer/mesh.h>
#include <renderer/shader.h>

namespace wind {

class DefaultRes {
public:
    static void load();
    static void free();

    static Shader* getParticleShader();
    static Shader* get2DShader();
    static Mesh* getReactangle();
    static Mesh* getCircle();
};

} // namespace wind