#include "mouse.h"

namespace wind {
    namespace system {
        namespace _internal {
            int MouseEventHandler::buttons_mask;
            int MouseEventHandler::click_mask;
            glm::vec2 MouseEventHandler::position;

            void MouseEventHandler::mousePressCallback(GLFWwindow*, int button, int action, int mods) {
                switch (action) {
                    case GLFW_PRESS:
                        buttons_mask ^= (1 << button);
                        click_mask &= ~(1 << button);
                        break;
                    case GLFW_RELEASE:
                        buttons_mask ^= (1 << button);
                        break;
                    default:
                        break;
                }
            }

            void MouseEventHandler::mouseMoveCallback(GLFWwindow*, double _x, double _y) {
                position.x = (float)_x;
                position.y = (float)_y;
            }
        }

        bool Mouse::isButton(int _button) {
            auto mask = _internal::MouseEventHandler::buttons_mask;
            return mask & (1 << _button);
        }

        bool Mouse::isButtonDown(int _button) {
            auto& mask = _internal::MouseEventHandler::click_mask;
            if (isButton(_button) && !(mask & (1 << _button))) {
                mask ^= (1 << _button);
                return true;
            }

            return false;
        }

        glm::vec2 Mouse::position() {
            return _internal::MouseEventHandler::position;
        }
    }
}