#include "../../utlis.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

namespace app {
    class Window {
    public:
        struct CreatingWindowConfig;
        GLFWwindow* m_window;
    private:
    public:
        Window(void (*)(CreatingWindowConfig* self));
        ~Window();
    };

    struct Window::CreatingWindowConfig {
        string title;
        vec2 size;
        vec2 pos;
    };
}