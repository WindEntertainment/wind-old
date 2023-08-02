#include "../shader/Shader.h"

namespace app {
    class Window {
    public:
        struct CreatingWindowConfig;
    private:
        ivec2 m_size;

        GLFWwindow* m_window;
        static void closeCallback(GLFWwindow* window);
    public:
        Window(void (*)(CreatingWindowConfig* self));
        ~Window();

        void show();

        ivec2 size();
    };

    struct Window::CreatingWindowConfig {
        string title = "glfw window";
        ivec2 size = {800, 600};
        ivec2 pos = {0, 0};
        
        ivec2 opengl_version = {3, 0};
    };
}