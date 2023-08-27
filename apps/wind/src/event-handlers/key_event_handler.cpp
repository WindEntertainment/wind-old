#include "./key_event_handler.h"

namespace app {
    namespace _internal {
        KeyEventHandler* KeyEventHandler::s_handler = new KeyEventHandler();
        
        void KeyEventHandler::keyCallback(GLFWwindow*, int key, int scancode, int action, int mods) {
            switch (action) {
                case GLFW_PRESS:
                    s_handler->keys_mask ^= (1 << key);
                    s_handler->click_mask &= ~(1 << key);
                    break;
                case GLFW_RELEASE:
                    s_handler->keys_mask ^= (1 << key);
                    break;
                default:
                    break;
            }
        }
    }

    bool Keyboard::isKey(int _key) {
        auto mask = _internal::KeyEventHandler::s_handler->keys_mask;
        return mask & (1 << _key);
    } 

    bool Keyboard::isKeyDown(int _key) {
        auto& mask = _internal::KeyEventHandler::s_handler->click_mask;
        if (isKey(_key) && !(mask & (1 << _key))) {
            mask ^= (1 << _key);
            return true;
        }

        return false;
    }
}