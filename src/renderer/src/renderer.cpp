// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/renderer.h"

#include <resources/default.h>

// clang-format on

namespace wind {

void Renderer::drawRectangle(ivec4 _rect, vec4 _color) {
    static const Mesh* rectangle = DefaultRes::getReactangle();
    static Shader* shader = DefaultRes::get2DShader();

    glm::mat4 model = glm::mat4(1);

    model = glm::translate(model, {_rect.x, _rect.y, 0});
    model = glm::scale(model, {_rect.x, _rect.y, 1});

    glBindVertexArray(rectangle->vao());

    shader->use();
    shader->uVec4f("color", _color);
    shader->uMat4f("model", model);

    glDrawElements(GL_TRIANGLES, rectangle->size(), GL_UNSIGNED_INT, 0);
}

} // namespace wind