#include "../application.h"

namespace wind {
    Window::Window(void (*buildConfig)(CreatingWindowConfig*)) {
        CreatingWindowConfig config;
        buildConfig(&config);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.opengl_version.x);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.opengl_version.y);
        m_window = glfwCreateWindow(
            config.size.x, config.size.y,
            config.title.c_str(),
            NULL, NULL
        );
        
        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1);

        glfwSetWindowCloseCallback(m_window, closeCallback);
        glfwSetKeyCallback(m_window, _internal::KeyEventHandler::keyCallback);
    
        m_size = config.size;
    }

    Window::~Window() {
        if (!m_window)
            return;
        glfwDestroyWindow(m_window);
    }

    void Window::show() {
        glfwSwapBuffers(m_window);
    }

    ivec2 Window::size() {
        return m_size;
    }

    void Window::closeCallback(GLFWwindow* window) {
        Application::instance()->quit();
    }
}