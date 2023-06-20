#include "./KeyEventHandler.h"

namespace app {
    namespace _internal {
        KeyEventHandler* KeyEventHandler::s_handler = new KeyEventHandler();
        
        void KeyEventHandler::keyCallback(GLFWwindow*, int key, int scancode, int action, int mods) {
            switch (action) {
                case GLFW_PRESS:
                    s_handler->keys.push_back(key);
                    break;
                case GLFW_RELEASE:
                    s_handler->keys.remove(key);
                    break;
                default:
                    break;
            }
        }
    }

    bool Keyboard::isKey(int _key) {
        auto keys = _internal::KeyEventHandler::s_handler->keys;
        auto it = std::find(keys.begin(), keys.end(), _key);
        return it != keys.end();
    } 
}