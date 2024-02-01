// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/renderer.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <resources/default.h>

// clang-format on

namespace wind {

namespace {

glm::mat4 orthoMatrix = glm::mat4(1);
glm::mat4 viewMatrix = glm::mat4(1);

} // namespace

void Renderer::drawRectangle(vec4 _rect, vec4 _color) {
    static const Mesh* rectangle = DefaultRes::getReactangle();
    static Shader* shader = DefaultRes::get2DShader();

    glm::mat4 model = glm::mat4(1);

    model = glm::translate(model, {_rect.x, _rect.y, 0});
    model = glm::scale(model, {_rect.z, _rect.w, 1});

    glBindVertexArray(rectangle->vao());

    shader->use();
    shader->uVec4f("color", _color);
    shader->uMat4f("model", model);
    shader->uMat4f("projection", orthoMatrix);
    shader->uMat4f("view", viewMatrix);

    glDrawElements(GL_TRIANGLES, rectangle->size(), GL_UNSIGNED_INT, 0);
}

void Renderer::drawCircle(vec2 _center, float _radius, vec4 _color) {
    static const Mesh* circle = DefaultRes::getCircle();
    static Shader* shader = DefaultRes::get2DShader();

    glm::mat4 model = glm::mat4(1);

    model = glm::translate(model, {_center.x, _center.y, 0});
    model = glm::scale(model, {_radius, _radius, 1});

    glBindVertexArray(circle->vao());

    shader->use();
    shader->uVec4f("color", _color);
    shader->uMat4f("model", model);
    shader->uMat4f("projection", orthoMatrix);
    shader->uMat4f("view", viewMatrix);

    glDrawElements(GL_TRIANGLES, circle->size(), GL_UNSIGNED_INT, 0);
}

void Renderer::clear(vec4 color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setOrtho(ivec2 _size) {
    // clang-format off
    orthoMatrix = glm::ortho(
        0.f, static_cast<float>(_size.x),
        0.f, static_cast<float>(_size.y),
        -1.f, 1.f);
    // clang-format on
}

void Renderer::updateCamera(vec2 _position) {
    viewMatrix = glm::mat4(1);
    viewMatrix = glm::translate(viewMatrix, vec3(_position, 0));
}

} // namespace wind