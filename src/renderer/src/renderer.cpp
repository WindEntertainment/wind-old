// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/renderer.h"

#include <resources/default.h>

// clang-format on

namespace wind {

void Renderer::drawRectangle(ivec4 _rect, ivec3 _color) {
    static const Mesh* rectangle = DefaultRes::getReactangle();
    static Shader* shader = DefaultRes::get2DShader();

    shader->use();
    glBindVertexArray(rectangle->vao());

    glDrawElements(GL_TRIANGLES, rectangle->size(), GL_UNSIGNED_INT, 0);
}

} // namespace wind