#include "Renderer.h"

namespace app {
    Renderer::Renderer(World* _world):
        m_world(_world) {};

    void Renderer::render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_world->shader->use();
        glBindVertexArray(m_world->mesh->VAO());
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}