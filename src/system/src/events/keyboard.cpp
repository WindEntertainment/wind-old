#include "keyboard.h"

namespace wind {
    namespace system {
        namespace _internal {
            int KeyEventHandler::keys_mask;
            int KeyEventHandler::click_mask;

            void KeyEventHandler::keyCallback(GLFWwindow*, int key, int scancode, int action, int mods) {
                switch (action) {
                    case GLFW_PRESS:
                        keys_mask ^= (1 << key);
                        click_mask &= ~(1 << key);
                        break;
                    case GLFW_RELEASE:
                        keys_mask ^= (1 << key);
                        break;
                    default:
                        break;
                }
            }
        }

        bool Keyboard::isKey(int _key) {
            auto mask = _internal::KeyEventHandler::keys_mask;
            return mask & (1 << _key);
        } 

        bool Keyboard::isKeyDown(int _key) {
            auto& mask = _internal::KeyEventHandler::click_mask;
            if (isKey(_key) && !(mask & (1 << _key))) {
                mask ^= (1 << _key);
                return true;
            }

            return false;
        }
    }
}