#include "renderer/mesh.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-formaton

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

    // glGenVertexArrays(1, &m_VAO);
    // glGenBuffers(1, &m_VBO);
    // glGenBuffers(1, &m_EBO);

    // glBindVertexArray(m_VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex),
    //              &m_vertices[0], GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint),
    //              m_indices.data(), GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    //                       (void *)offsetof(Vertex, tex_coords));

    // glBindVertexArray(0);

        // Vertex data
    float vertices[] = {
        // positions         // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Create VAO, VBO, and EBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    // Bind VAO
    glBindVertexArray(m_VAO);
    // Bind VBO and set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind EBO and set index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Unbind VAO, VBO, and EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

} // namespace wind
