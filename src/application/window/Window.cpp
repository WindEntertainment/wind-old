#include "../Application.h"

namespace app {
    Window::Window(void (*buildConfig)(CreatingWindowConfig*)) {
        CreatingWindowConfig config;
        buildConfig(&config);

        m_window = glfwCreateWindow(
            config.size.x, config.size.y,
            config.title.c_str(),
            NULL, NULL
        );
        
        glfwMakeContextCurrent(m_window);

        glfwSetWindowCloseCallback(m_window, closeCallback);
    }

    Window::~Window() {
        if (!m_window)
            return;
        glfwDestroyWindow(m_window);
    }

    void Window::closeCallback(GLFWwindow* window) {
        Application::instance()->quit();
    }
}