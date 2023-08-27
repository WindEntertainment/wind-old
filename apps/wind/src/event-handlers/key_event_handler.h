#include "logger.h"
#include "../utils.h"

namespace app {
    class Keyboard final {
    public:
        static bool isKey(int key);
        static bool isKeyDown(int key);
    };

    namespace _internal {
        class KeyEventHandler final {
            friend class app::Keyboard;
        private:
            static KeyEventHandler* s_handler;
        public:
            static void keyCallback(GLFWwindow*, int, int, int, int);
        private:
            int keys_mask;
            int click_mask;
        };
    }
}