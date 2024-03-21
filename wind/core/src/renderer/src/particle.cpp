#include "renderer/particle.h"
#include "renderer/shader.h"
#include "resources/default.h"

// clang-format off
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
// clang-format on

namespace wind {

ParticleSystem::ParticleSystem(std::vector<glm::vec3> _vertices, std::vector<uint> _indicies,
                               std::vector<glm::vec2> _uv, size_t _count) {
  assert(_vertices.size() == _uv.size());

  m_vertices.resize(_vertices.size());
  for (uint i = 0; i < m_vertices.size(); ++i)
    m_vertices[i] = {_vertices[i], _uv[i]};

  m_indices = _indicies;
  m_models.resize(_count);

  //====================================//

  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);
  glGenBuffers(1, &m_MBO);

  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER,
               m_vertices.size() * sizeof(Vertex),
               &m_vertices[0],
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               m_indices.size() * sizeof(uint),
               m_indices.data(),
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex),
                        (void*)offsetof(Vertex, tex_coords));

  glBindBuffer(GL_ARRAY_BUFFER, m_MBO);
  glBufferData(GL_ARRAY_BUFFER,
               m_models.size() * sizeof(glm::mat4),
               &m_models[0],
               GL_STATIC_DRAW);

  std::size_t vec4Size = sizeof(glm::vec4);
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(
      4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
  glEnableVertexAttribArray(5);
  glVertexAttribPointer(
      5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
  glEnableVertexAttribArray(6);
  glVertexAttribPointer(
      6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);
  glVertexAttribDivisor(5, 1);
  glVertexAttribDivisor(6, 1);

  glBindVertexArray(0);
}

ParticleSystem::~ParticleSystem() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
  glDeleteBuffers(1, &m_EBO);
  glDeleteBuffers(1, &m_MBO);
}

uint ParticleSystem::vao() const {
  return m_VAO;
}

uint ParticleSystem::size() const {
  return m_indices.size();
}

void ParticleSystem::setPosition(uint _i, glm::vec2 _position) {
  m_models[_i] = glm::mat4(1);
  m_models[_i] = glm::translate(m_models[_i], {_position, 0.f});

  float scale = 10.f;
  m_models[_i] = glm::scale(m_models[_i], glm::vec3(scale, scale, 1));
}

void ParticleSystem::draw(glm::mat4 _orthoMatrix, glm::mat4 _viewMatrix) {
  static Shader* shader = DefaultRes::getParticleShader();
  static glm::vec4 color = {0.8f, 0.8f, 0.8f, 1.f};

  shader->use();
  shader->uVec4f("color", color);
  shader->uMat4f("projection", _orthoMatrix);
  shader->uMat4f("view", _viewMatrix);

  glBindVertexArray(vao());

  glBindBuffer(GL_ARRAY_BUFFER, m_MBO);
  glBufferData(GL_ARRAY_BUFFER,
               m_models.size() * sizeof(glm::mat4),
               &m_models[0],
               GL_STATIC_DRAW);

  glDrawElementsInstanced(
      GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0, m_models.size());
}

} // namespace wind
