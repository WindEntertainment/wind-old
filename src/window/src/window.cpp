// clang-format off
#include <glad/glad.h>
// clang-format on

#include "window/window.h"

#include "window/events/keyboard.h"
#include "window/events/mouse.h"

#include <spdlog/spdlog.h>

namespace wind {

Window::Window(void (*buildConfig)(WindowConfig *)) {
    WindowConfig config;
    buildConfig(&config);

    glfwWindowHint(GLFW_RESIZABLE, config.resizable);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.openglVersion.x);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.openglVersion.y);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(
        config.size.x, config.size.y, config.title.c_str(),
        config.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!m_window) {
        spdlog::error("Cannot create window {}", getGLFWError());
        return;
    }

    onCloseEvent = config.onCloseEvent;

    glfwSetWindowUserPointer(m_window, this);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    glfwSetWindowCloseCallback(m_window, closeCallback);
    glfwSetKeyCallback(m_window, _internal::KeyEventHandler::keyCallback);
    glfwSetCursorPosCallback(m_window,
                             _internal::MouseEventHandler::mouseMoveCallback);
    glfwSetMouseButtonCallback(
        m_window, _internal::MouseEventHandler::mousePressCallback);

    glfwSetInputMode(m_window, GLFW_CURSOR,
                     config.cursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

    m_size = config.size;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Cannot GLAD load GLLoader");
        return;
    }

    glViewport(0, 0, config.size.x, config.size.y);
}

Window::~Window() {
    if (!m_window)
        return;
    glfwDestroyWindow(m_window);
}

void Window::show() {
    if (!m_window)
        return;
    glfwSwapBuffers(m_window);
    _internal::MouseEventHandler::clearOffset();
}

void Window::cursorDisable() {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

ivec2 Window::size() {
    return m_size;
}

void Window::closeCallback(GLFWwindow *gl_window) {
    auto window = (Window *)glfwGetWindowUserPointer(gl_window);
    if (window->onCloseEvent)
        window->onCloseEvent();
}

const char *Window::getGLFWError() {
    const char *description;
    glfwGetError(&description);
    return description;
}

} // namespace wind