#include "mouse.h"

namespace wind {
    namespace system {
        namespace _internal {
            int MouseEventHandler::buttons_mask;
            int MouseEventHandler::click_mask;
            glm::vec2 MouseEventHandler::position;
            glm::vec2 MouseEventHandler::offset;

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
                offset = {
                    _x - position.x,
                    position.y - _y
                };
                
                position = {
                    (float)_x,
                    (float)_y
                };
            }

            void MouseEventHandler::clearOffset() {
                offset = {};
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

        glm::vec2 Mouse::offset() {
            return _internal::MouseEventHandler::offset;
        }
    }
}