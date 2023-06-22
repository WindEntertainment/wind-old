#include "Renderer.h"

namespace app {
    Renderer::Renderer() {
        vertices = new float[9]{
            0.0f,  0.5f,  0.0f,
            0.5f, -0.5f,  0.0f,
           -0.5f, -0.5f,  0.0f
        };

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(
            GL_ARRAY_BUFFER, 9 * sizeof(float),
            vertices, GL_STATIC_DRAW
        );

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    Renderer::~Renderer() {
        delete[] vertices;
    }
}