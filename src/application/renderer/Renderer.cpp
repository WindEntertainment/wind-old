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

        auto transform = model->entity()->getComponent<Transform>();

        glm::mat4 matrix_model = glm::mat4(1);

        matrix_model = glm::rotate(matrix_model, glm::radians(transform->rotation.x), vec3{1, 0, 0});
        matrix_model = glm::rotate(matrix_model, glm::radians(transform->rotation.y), vec3{0, 1, 0});
        matrix_model = glm::rotate(matrix_model, glm::radians(transform->rotation.z), vec3{0, 0, 1});
        
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, transform->position); 

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        model->shader->uMat4f("model", matrix_model);
        model->shader->uMat4f("view", view);
        model->shader->uMat4f("projection", projection);

        glDrawElements(GL_TRIANGLES, model->mesh->size(), GL_UNSIGNED_INT, 0);
    }
}