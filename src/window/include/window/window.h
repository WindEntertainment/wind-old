#pragma once
#include <GLFW/glfw3.h>
#include <utils/utils.h>

namespace wind {

class Window {
public:
    struct WindowConfig;

private:
    ivec2 m_size;

    std::function<void()> onCloseEvent;

    GLFWwindow *m_window;
    static void closeCallback(GLFWwindow *window);

    const char *getGLFWError();

public:
    Window(void (*)(WindowConfig *self));
    ~Window();

    void cursorDisable();

    void show();
    ivec2 size();
};

struct Window::WindowConfig {
    string title = "Wind";
    ivec2 size = {800, 600};
    ivec2 pos = {0, 0};
    bool fullscreen = true;
    bool resizable = false;
    bool cursor = true;
    std::function<void()> onCloseEvent;

    ivec2 openglVersion{3, 3};
};

} // namespace wind