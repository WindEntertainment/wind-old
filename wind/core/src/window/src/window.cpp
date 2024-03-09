// clang-format off
#include <spdlog/spdlog.h>

#include <chrono>
#include <ctime>

#include <resources/default.h>
#include <renderer/renderer.h>

#include "window/window.h"
#include "window/events/keyboard.h"
#include "window/events/mouse.h"
// clang-format on

namespace wind {

namespace {

static bool m_alive;
static const char* m_title;
static bool m_vsync;
static GLFWwindow* m_window;
static int m_fps;

using timepoint = chrono::time_point<chrono::high_resolution_clock>;
static timepoint m_perSecond;

} // namespace

//===========================================//
// Lifecycle

void Window::init(void (*buildConfig)(Config*)) {
    Config config;
    buildConfig(&config);

    if (!glfwInit()) {
        spdlog::error("Cannot glfw init: {}", getGLFWError());
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, config.resizable);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.openglVersion.x);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.openglVersion.y);

#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(
        config.size.x, config.size.y, config.title.c_str(),
        config.fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!m_window) {
        spdlog::error("Cannot create window {}", getGLFWError());
        return;
    }

    m_alive = true;
    m_vsync = config.vSync;
    m_title = config.title.c_str();

    atexit(destroy);

    glfwMakeContextCurrent(m_window);
    setVsync(m_vsync);

    glfwSetWindowCloseCallback(m_window, closeCallback);
    glfwSetKeyCallback(m_window, _internal::KeyEventHandler::keyCallback);

    glfwSetCursorPosCallback(m_window,
                             _internal::MouseEventHandler::mouseMoveCallback);
    glfwSetMouseButtonCallback(
        m_window, _internal::MouseEventHandler::mousePressCallback);
    glfwSetScrollCallback(m_window,
                          _internal::MouseEventHandler::mouseScrollCallback);

    setVisiableCursor(config.visibleCursor);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Cannot GLAD load GLLoader");
        return;
    }

    glViewport(0, 0, config.size.x, config.size.y);

    DefaultRes::load();
    Renderer::setOrtho(config.size);
}

void Window::destroy() {
    if (!m_window)
        return;

    DefaultRes::free();
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
    _internal::MouseEventHandler::clearOffset();
    glfwPollEvents();
    return m_alive;
}

void Window::close() {
    m_alive = false;
}

//===========================================//
// Setters

void Window::setTitle(const char* _title) {
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

const char* Window::title() {
    return m_title;
}

ivec2 Window::size() {
    int w, h;
    glfwGetWindowPos(m_window, &w, &h);
    return {w, h};
}

ivec2 Window::position() {
    int x, y;
    glfwGetWindowPos(m_window, &x, &y);
    return {x, y};
}

bool Window::isFullscreen() {
    return glfwGetWindowMonitor(m_window);
}

bool Window::isResizable() {
    return glfwGetWindowAttrib(m_window, GLFW_RESIZABLE);
}

bool Window::isVisiableCursor() {
    return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
}

int Window::getFPS() {
    return m_fps;
}

//===========================================//
// internal

void Window::closeCallback(GLFWwindow* gl_window) {
    m_alive = false;
}

const char* Window::getGLFWError() {
    const char* description;
    glfwGetError(&description);
    return description;
}

} // namespace wind
