#include "renderer.h"

namespace wind {
    namespace renderer {
        void Renderer::clear() {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        }

        void Renderer::render(Camera* camera, Mesh* mesh, vec3 position, vec3 rotation, vec3 scale) {
            mesh->shader()->use();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mesh->texture()->id());

            glBindVertexArray(mesh->VAO()); 

            glm::mat4 matrix_model = glm::mat4(1);

            matrix_model = glm::translate(matrix_model, position);
            matrix_model = glm::rotate(matrix_model, glm::radians(rotation.x), vec3{1, 0, 0});
            matrix_model = glm::rotate(matrix_model, glm::radians(rotation.y), vec3{0, 1, 0});
            matrix_model = glm::rotate(matrix_model, glm::radians(rotation.z), vec3{0, 0, 1});
            matrix_model = glm::scale(matrix_model, scale);

            glm::mat4 view;
            if (camera)
                view = glm::lookAt(
                    camera->position,
                    camera->position + camera->front,
                    camera->up
                );

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 1280.0f / 860.0f, 0.1f, 100.0f);

            mesh->shader()->uMat4f("model", matrix_model);
            mesh->shader()->uMat4f("view", view);
            mesh->shader()->uMat4f("projection", projection);

            glDrawElements(GL_TRIANGLES, mesh->size(), GL_UNSIGNED_INT, 0);
        }
    }
}