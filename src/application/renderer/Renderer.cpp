#include "Renderer.h"

namespace app {
    Renderer::Renderer(Shader* _shader) {
        m_shader = _shader;
        m_vertices = new float[9]{
            0.0f,  0.5f,  0.0f,
            0.5f, -0.5f,  0.0f,
           -0.5f, -0.5f,  0.0f
        };

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(
            GL_ARRAY_BUFFER, 9 * sizeof(float),
            m_vertices, GL_STATIC_DRAW
        );

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
        m_shader->use();
        glBindVertexArray(m_VAO);
    }

    Renderer::~Renderer() {
        delete[] m_vertices;
    }

    void Renderer::draw() {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}