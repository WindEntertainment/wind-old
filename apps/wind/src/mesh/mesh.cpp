#include "mesh.h"

namespace wind {
    uint Mesh::VAO() {
        return m_VAO;
    }

    uint Mesh::size() {
        return m_mesh->indices.size();
    }

    Mesh::Mesh(assets::Mesh* _mesh, Shader* _shader) {
        m_mesh = _mesh;
        shader = _shader;

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);        
        glBufferData(
            GL_ARRAY_BUFFER, _mesh->vertices.size() * sizeof(float) * 3,
            _mesh->vertices.data(), GL_STATIC_DRAW
        );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); 
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, _mesh->indices.size() * sizeof(uint),
            _mesh->indices.data(), GL_STATIC_DRAW
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