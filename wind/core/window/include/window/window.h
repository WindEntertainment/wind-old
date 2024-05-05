#pragma once

// clang-format off
#include "utils.h"

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
  static void init(Config);

  static void destroy();

  // setters
  static void setTitle(const char* title);
  static void setSize(glm::ivec2 size);
  static void setPosition(glm::ivec2 position);
  static void setResizable(bool resizable = true);
  static void setVisiableCursor(bool visiableCursor = true);
  static void setVsync(bool enable);

  // getters
  static const char* title();
  static glm::ivec2 size();
  static glm::ivec2 position();
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
  std::string title = "Wind";
  glm::ivec2 size = {800, 600};
  glm::ivec2 position = {0, 0};
  bool fullScreen = true;
  bool resizable = false;
  bool visibleCursor = true;
  bool vSync = true;

  glm::ivec2 openglVersion{3, 3};
};

} // namespace wind
