#pragma once

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utils/utils.h>

#include "window/events/keyboard.h" // IWYU pragma: export
#include "window/events/mouse.h"    // IWYU pragma: export
// clang-format on

namespace wind {

class Window {
public:
  struct Config;

private:
  static void closeCallback(GLFWwindow* window);
  static const char* getGLFWError();

public:
  static void init(void (*)(Config* self));
  static void destroy();

  // setters
  static void setTitle(const char* title);
  static void setSize(ivec2 size);
  static void setPosition(ivec2 position);
  static void setResizable(bool resizable = true);
  static void setVisiableCursor(bool visiableCursor = true);
  static void setVsync(bool enable);

  // getters
  static const char* title();
  static ivec2 size();
  static ivec2 position();
  static bool isFullscreen();
  static bool isResizable();
  static bool isVisiableCursor();
  static bool isVsync();
  static int getFPS();

  // lifecycle
  static void close();
  static bool update();
  static void show();
};

struct Window::Config {
  string title = "Wind";
  ivec2 size = {800, 600};
  ivec2 position = {0, 0};
  bool fullScreen = true;
  bool resizable = false;
  bool visibleCursor = true;
  bool vSync = true;

  ivec2 openglVersion{3, 3};
};

} // namespace wind
