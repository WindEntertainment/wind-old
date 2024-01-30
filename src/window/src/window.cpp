
#include "window/window.h"
#include <chrono>
#include <ctime>

#include "window/events/keyboard.h"
#include "window/events/mouse.h"

#include <spdlog/spdlog.h>

namespace wind {

//===========================================//
// Lifecycle

Window::Window(void (*buildConfig)(Config *)) {
    Config config;
    buildConfig(&config);

    if (!glfwInit()) {
        spdlog::error("Cannot glfw init: {}", getGLFWError());
        return;
    }

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

    m_alive = true;
    m_vsync = config.vsync;
    m_title = config.title.c_str();

    glfwSetWindowUserPointer(m_window, this);

    glfwMakeContextCurrent(m_window);
    setVsync(m_vsync);

    glfwSetWindowCloseCallback(m_window, closeCallback);
    glfwSetKeyCallback(m_window, _internal::KeyEventHandler::keyCallback);
    glfwSetCursorPosCallback(m_window,
                             _internal::MouseEventHandler::mouseMoveCallback);
    glfwSetMouseButtonCallback(
        m_window, _internal::MouseEventHandler::mousePressCallback);

    setVisiableCursor(config.visableCursor);

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
    static const auto oneSecond = std::chrono::duration_cast<
        std::chrono::high_resolution_clock::duration>(std::chrono::seconds(1));
    static int numFrames = 0;

    glfwSwapBuffers(m_window);

    numFrames += 1;
    if (chrono::high_resolution_clock::now() > m_perSecond) {
        m_fps = numFrames;
        numFrames = 0;

        m_perSecond = chrono::high_resolution_clock::now() + oneSecond;
    }
}

bool Window::update() {
    glfwPollEvents();
    _internal::MouseEventHandler::clearOffset();
    return m_alive;
}

void Window::close() {
    m_alive = false;
}

//===========================================//
// Setters

void Window::setTitle(const char *_title) {
    glfwSetWindowTitle(m_window, _title);
    m_title = _title;
}

void Window::setSize(ivec2 _size) {
    glfwSetWindowSize(m_window, _size.x, _size.y);
    glViewport(0, 0, _size.x, _size.y);
}

void Window::setPosition(ivec2 _position) {
    glfwSetWindowPos(m_window, _position.x, _position.y);
}

void Window::setResizable(bool _resizable) {
    glfwWindowHint(GLFW_RESIZABLE, _resizable);
}

void Window::setVisiableCursor(bool _visable) {
    glfwSetInputMode(m_window, GLFW_CURSOR,
                     _visable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Window::setVsync(bool _enable) {
    glfwSwapInterval(_enable);
}

//===========================================//
// Getters

const char *Window::title() const {
    return m_title;
}

ivec2 Window::size() const {
    int w, h;
    glfwGetWindowPos(m_window, &w, &h);
    return {w, h};
}

ivec2 Window::position() const {
    int x, y;
    glfwGetWindowPos(m_window, &x, &y);
    return {x, y};
}

bool Window::isFullscreen() const {
    return glfwGetWindowMonitor(m_window);
}

bool Window::isResizable() const {
    return glfwGetWindowAttrib(m_window, GLFW_RESIZABLE);
}

bool Window::isVisiableCursor() const {
    return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
}

int Window::getFPS() const {
    return m_fps;
}

//===========================================//
// internal

void Window::closeCallback(GLFWwindow *gl_window) {
    auto window = (Window *)glfwGetWindowUserPointer(gl_window);
    window->m_alive = false;
}

const char *Window::getGLFWError() {
    const char *description;
    glfwGetError(&description);
    return description;
}

} // namespace wind