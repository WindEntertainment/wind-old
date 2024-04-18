#pragma once
#include <renderer/mesh.hpp>
#include <renderer/shader.hpp>

namespace wind {

class DefaultRes {
public:
  static void load();
  static void free();

  static Shader* getParticleShader();
  static Shader* get2DShader();
  static Mesh* getRectangle();
  static Mesh* getCircle();
};

} // namespace wind
