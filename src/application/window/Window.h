#include "../event-handlers/KeyEventHandler.h"

namespace app {
    class Window {
    public:
        struct CreatingWindowConfig;
        GLFWwindow* m_window;
    private:
        static void closeCallback(GLFWwindow* window);
    public:
        Window(void (*)(CreatingWindowConfig* self));
        ~Window();
    };

    struct Window::CreatingWindowConfig {
        string title = "glfw window";
        ivec2 size = {800, 600};
        ivec2 pos = {0, 0};
        
        ivec2 opengl_version = {3, 0};
    };
}