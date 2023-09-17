#include "../utils.h"

namespace wind {
    namespace system {
        class Keyboard final {
        public:
            static bool isKey(int key);
            static bool isKeyDown(int key);
        };
        
        namespace _internal {
            class KeyEventHandler final {
                friend class wind::system::Keyboard;
            public:
                static void keyCallback(GLFWwindow*, int, int, int, int);
            private:
                static int keys_mask;
                static int click_mask;
            };
        }
    }
}