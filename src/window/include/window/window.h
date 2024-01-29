#pragma once
#include <GLFW/glfw3.h>
#include <utils/utils.h>

namespace wind {

class Window {
public:
    struct Config;

private:
    bool m_alive;
    ivec2 m_size;

    GLFWwindow *m_window;
    static void closeCallback(GLFWwindow *window);

    const char *getGLFWError();

public:
    Window(void (*)(Config *self));
    ~Window();

    void cursorDisable();

    bool update();
    void show();

    ivec2 size();
};

struct Window::Config {
    string title = "Wind";
    ivec2 size = {800, 600};
    ivec2 pos = {0, 0};
    bool fullscreen = true;
    bool resizable = false;
    bool cursor = true;

    ivec2 openglVersion{3, 3};
};

} // namespace wind