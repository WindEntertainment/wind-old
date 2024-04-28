#pragma once
#include "../utils.h"

namespace wind {

class Keyboard final {
public:
  static bool isKey(int key);
  static bool isKeyDown(int key);
};

namespace _internal {

class KeyEventHandler final {
  friend class wind::Keyboard;

public:
  static void keyCallback(GLFWwindow*, int, int, int, int);

private:
  static int s_keysMask;
  static int s_clickMask;
};

} // namespace _internal
} // namespace wind
