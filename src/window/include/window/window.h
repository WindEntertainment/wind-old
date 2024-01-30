#pragma once
#include <GLFW/glfw3.h>
#include <utils/utils.h>

namespace wind {

class Window {
public:
    struct Config;

private:
    bool m_alive;
    int m_targetFps;
    const char *m_title;

    GLFWwindow *m_window;
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
    void setTargetFPS(int fps);

    // getters
    const char *title() const;
    ivec2 size() const;
    ivec2 position() const;
    bool isFullscreen() const;
    bool isResizable() const;
    bool isVisiableCursor() const;
    int getTargetFPS() const;

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
    int targetFPS = 120;

    ivec2 openglVersion{3, 3};
};

} // namespace wind