#include "renderer.h"

namespace wind {
    namespace renderer {
        void Renderer::clear() {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void Renderer::render(Mesh* mesh, vec3 position, vec3 rotation) {
            mesh->shader()->use();
            glBindVertexArray(mesh->VAO());

            glm::mat4 matrix_model = glm::mat4(1);

            matrix_model = glm::rotate(matrix_model, glm::radians(rotation.x), vec3{1, 0, 0});
            matrix_model = glm::rotate(matrix_model, glm::radians(rotation.y), vec3{0, 1, 0});
            matrix_model = glm::rotate(matrix_model, glm::radians(rotation.z), vec3{0, 0, 1});
            
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::translate(view, position); 

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

            mesh->shader()->uMat4f("model", matrix_model);
            mesh->shader()->uMat4f("view", view);
            mesh->shader()->uMat4f("projection", projection);

            glDrawElements(GL_TRIANGLES, mesh->size(), GL_UNSIGNED_INT, 0);
        }
    }
}