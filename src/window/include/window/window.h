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
    inline void setTitle(const char *title);
    inline void setSize(ivec2 size);
    inline void setPosition(ivec2 position);
    inline void setResizable(bool resizable = true);
    inline void setVisiableCursor(bool visiableCursor = true);
    inline void setTargetFPS(int fps);

    // getters
    inline const char *title() const;
    inline ivec2 size() const;
    inline ivec2 position() const;
    inline bool isFullscreen() const;
    inline bool isResizable() const;
    inline bool isVisiableCursor() const;
    inline int getTargetFPS() const;

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