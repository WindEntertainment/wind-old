#include "window/events/keyboard.h"

namespace wind {

namespace _internal {

int KeyEventHandler::s_keysMask;
int KeyEventHandler::s_clickMask;

void KeyEventHandler::keyCallback(GLFWwindow*, int _key, int _scancode,
                                  int _action, int _mods) {
  switch (_action) {
  case GLFW_PRESS:
    s_keysMask ^= (1 << _key);
    s_clickMask &= ~(1 << _key);
    break;
  case GLFW_RELEASE:
    s_keysMask ^= (1 << _key);
    break;
  default:
    break;
  }
}

} // namespace _internal

bool Keyboard::isKey(int _key) {
  auto mask = _internal::KeyEventHandler::s_keysMask;
  return mask & (1 << _key);
}

bool Keyboard::isKeyDown(int _key) {
  auto& mask = _internal::KeyEventHandler::s_clickMask;
  if (isKey(_key) && !(mask & (1 << _key))) {
    mask ^= (1 << _key);
    return true;
  }

  return false;
}

} // namespace wind
