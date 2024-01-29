#include "window/events/mouse.h"

namespace wind {
namespace _internal {

int MouseEventHandler::s_buttonsMask;
int MouseEventHandler::s_clickMask;
glm::vec2 MouseEventHandler::s_position;
glm::vec2 MouseEventHandler::s_offset;

void MouseEventHandler::mousePressCallback(GLFWwindow *, int _button,
                                           int _action, int _mods) {
    switch (_action) {

    case GLFW_PRESS:
        s_buttonsMask ^= (1 << _button);
        s_clickMask &= ~(1 << _button);
        break;

    case GLFW_RELEASE:
        s_buttonsMask ^= (1 << _button);
        break;

    default:
        break;
    }
}

void MouseEventHandler::mouseMoveCallback(GLFWwindow *, double _x, double _y) {
    s_offset = {static_cast<float>(_x) - s_position.x,
                s_position.y - static_cast<float>(_y)};

    s_position = {(float)_x, (float)_y};
}

void MouseEventHandler::clearOffset() {
    s_offset = {};
}

} // namespace _internal

bool Mouse::isButton(int _button) {
    auto mask = _internal::MouseEventHandler::s_buttonsMask;
    return mask & (1 << _button);
}

bool Mouse::isButtonDown(int _button) {
    auto &mask = _internal::MouseEventHandler::s_clickMask;
    if (isButton(_button) && !(mask & (1 << _button))) {
        mask ^= (1 << _button);
        return true;
    }

    return false;
}

glm::vec2 Mouse::position() {
    return _internal::MouseEventHandler::s_position;
}

glm::vec2 Mouse::offset() {
    return _internal::MouseEventHandler::s_offset;
}

} // namespace wind