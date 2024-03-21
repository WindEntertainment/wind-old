#include "renderer/mesh.h"

namespace wind {

uint Mesh::vao() const {
  return m_VAO;
}

uint Mesh::ebo() const {
  return m_EBO;
}

uint Mesh::size() const {
  return m_indices.size();
}

Mesh::Mesh(std::vector<glm::vec3> _vertices, std::vector<uint> _indicies, std::vector<glm::vec2> _uv) {
  assert(_vertices.size() == _uv.size());

  m_vertices.resize(_vertices.size());
  for (uint i = 0; i < m_vertices.size(); ++i)
    m_vertices[i] = {_vertices[i], _uv[i]};

  m_indices = _indicies;

  //====================================//

  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint), m_indices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

  glBindVertexArray(0);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
  glDeleteBuffers(1, &m_EBO);
}

} // namespace wind
