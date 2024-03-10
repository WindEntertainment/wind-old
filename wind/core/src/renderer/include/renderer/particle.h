#pragma once
#include <utils/utils.h>

namespace wind {

struct ParticleSystem {
public:
  glm::vec2 position;
  glm::vec2 rotation;
  glm::vec2 scale;

  ParticleSystem(std::vector<glm::vec3> vertices, std::vector<uint> indicies, std::vector<glm::vec2> uv,
                 size_t count);
  ~ParticleSystem();

  uint vao() const;
  uint size() const;
  void draw(glm::mat4 _orthoMatrix, glm::mat4 _viewMatrix);

  void setPosition(uint _i, glm::vec2 position);

private:
  struct Vertex {
    glm::vec3 position;
    glm::vec2 tex_coords;
  };

  uint m_VAO, m_VBO, m_EBO, m_MBO;
  std::vector<Vertex> m_vertices;
  std::vector<uint> m_indices;

  std::vector<glm::mat4> m_models;
};

} // namespace wind
