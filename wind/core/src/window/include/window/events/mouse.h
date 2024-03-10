#pragma once
#include <GLFW/glfw3.h>
#include <utils/utils.h>

namespace wind {

class Mouse final {
public:
  static bool isButton(int button);
  static bool isButtonDown(int button);

  static glm::vec2 position();
  static glm::vec2 offset();

  static glm::vec2 scroll();
  static float yScroll();
  static float xScroll();
};

namespace _internal {
class MouseEventHandler final {
  friend class wind::Mouse;

public:
  static void clearOffset();
  static void mouseMoveCallback(GLFWwindow*, double, double);
  static void mousePressCallback(GLFWwindow*, int, int, int);
  static void mouseScrollCallback(GLFWwindow*, double, double);

private:
  static int s_buttonsMask;
  static int s_clickMask;
  static glm::vec2 s_position;
  static glm::vec2 s_offset;
  static glm::vec2 s_scroll;
};

} // namespace _internal
} // namespace wind
