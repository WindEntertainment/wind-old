#pragma once
#include "utils.h"

namespace wind {

struct Mesh {
private:
  struct Vertex {
    glm::vec3 position;
    glm::vec2 tex_coords;
  };

private:
  uint m_VAO, m_VBO, m_EBO;
  std::vector<Vertex> m_vertices;
  std::vector<uint> m_indices;

public:
  Mesh(std::vector<glm::vec3> vertices, std::vector<uint> indicies, std::vector<glm::vec2> uv);
  ~Mesh();

  uint vao() const;
  uint ebo() const;
  uint size() const;
};

} // namespace wind
