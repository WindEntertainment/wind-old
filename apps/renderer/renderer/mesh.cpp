#include "mesh.h"

namespace wind {
    namespace renderer {
        Shader* Mesh::shader() {
            return m_shader;
        }

        uint Mesh::VAO() {
            return m_VAO;
        }

        uint Mesh::size() {
            return m_indices.size();
        }

        Mesh::Mesh(vector<vec3> _vertices, vector<uint> _indicies, Shader* _shader) {
            m_vertices = _vertices;
            m_indices = _indicies;
            m_shader = _shader;

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_EBO);

            glBindVertexArray(m_VAO);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);        
            glBufferData(
                GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float) * 3,
                m_vertices.data(), GL_STATIC_DRAW
            );

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); 
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint),
                m_indices.data(), GL_STATIC_DRAW
            );

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        Mesh::~Mesh() {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_EBO);
        }
    }
}