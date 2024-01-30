#pragma once

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-formaton

#include <window/events/keyboard.h>
#include <window/events/mouse.h>

#include <chrono>
#include <utils/utils.h>

namespace wind {

class Window {
public:
    struct Config;

private:
    bool m_alive;
    const char *m_title;
    bool m_vsync;

    GLFWwindow *m_window;

    int m_fps;

    using timepoint = chrono::time_point<chrono::high_resolution_clock>;
    timepoint m_perSecond;

    static void closeCallback(GLFWwindow *window);

    const char *getGLFWError();

public:
    Window(void (*)(Config *self));
    ~Window();

    // setters
    void setTitle(const char *title);
    void setSize(ivec2 size);
    void setPosition(ivec2 position);
    void setResizable(bool resizable = true);
    void setVisiableCursor(bool visiableCursor = true);
    // void setTargetFPS(int fps);
    void setVsync(bool enable);

    // getters
    const char *title() const;
    ivec2 size() const;
    ivec2 position() const;
    bool isFullscreen() const;
    bool isResizable() const;
    bool isVisiableCursor() const;
    bool isVsync() const;
    // int getTargetFPS() const;
    int getFPS() const;

    // lifecycle
    void close();
    bool update();
    void show();
};

struct Window::Config {
    string title = "Wind";
    ivec2 size = {800, 600};
    ivec2 position = {0, 0};
    bool fullscreen = true;
    bool resizable = false;
    bool visableCursor = true;
    bool vsync = true;

    ivec2 openglVersion{3, 3};
};

} // namespace wind