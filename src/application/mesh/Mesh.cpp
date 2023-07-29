#include "Mesh.h"

namespace app {
    uint Mesh::VBO() {
        return m_VBO;
    }

    Mesh::Mesh(std::vector<vec3> _vertices, std::vector<uint> _indices) {
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(
            GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float),
            m_vertices.data(), GL_STATIC_DRAW
        );
        
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);            
    }
}