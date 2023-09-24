#include "../utils.h"

namespace wind {
    namespace system {
        class Mouse final {
        public:
            static bool isButton(int button);
            static bool isButtonDown(int button);

            static glm::vec2 position();
        };

        namespace _internal {
            class MouseEventHandler final {
                friend class wind::system::Mouse;
            public:
                static void mouseMoveCallback(GLFWwindow*, double, double);
                static void mousePressCallback(GLFWwindow*, int, int, int);
            private:
                static int buttons_mask;
                static int click_mask;
                static glm::vec2 position;
            };
        }
    }
}