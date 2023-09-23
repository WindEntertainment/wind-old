#include "utils.h"

namespace wind {
    namespace system {
        class Window {
        public:
            struct WindowConfig;
        private:
            ivec2 m_size;

            std::function<void()> close_event;

            GLFWwindow* m_window;
            static void closeCallback(GLFWwindow* window);
        public:
            Window(void (*)(WindowConfig* self));
            ~Window();

            void show();
            ivec2 size();
        };

        struct Window::WindowConfig {
            string title = "Wind";
            ivec2 size = {800, 600};
            ivec2 pos = {0, 0};
            bool fullscreen = true;
            bool resizable = false;
            std::function<void()> close_event;
            
            ivec2 opengl_version = {3, 3};
        };
    }
}