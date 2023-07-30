#include "Renderer.h"

namespace app {
    Renderer::Renderer(World* _world):
        m_world(_world) {};

    void Renderer::render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto models = World::findAllWithComponent<Model>();
        auto model = models.front();
        
        model->shader->use();
        glBindVertexArray(model->mesh->VAO());

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}