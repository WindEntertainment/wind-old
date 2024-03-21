#include "input-system/mouse-context.h"
#include "input-system/keys.h"

namespace wind {
void MouseContext::addPressedButton(KEYCODES keycode) {
  pressedButtons.insert(keycode);
};
void MouseContext::addHeldButton(KEYCODES keycode) {
  heldButtons.insert(keycode);
};
void MouseContext::addReleasedButton(KEYCODES keycode) {
  releasedButtons.insert(keycode);
};

void MouseContext::removePressedButton(KEYCODES keycode) {
  pressedButtons.erase(keycode);
};
void MouseContext::removeHeldButton(KEYCODES keycode) {
  heldButtons.erase(keycode);
};
void MouseContext::removeReleasedButton(KEYCODES keycode) {
  releasedButtons.erase(keycode);
};

void MouseContext::moveCursor(double nextX, double nextY) {
  cursorX = nextX;
  cursorY = nextY;
}

void MouseContext::moveScroll(double nextX, double nextY) {
  scrollX = nextX;
  scrollY = nextY;
}

} // namespace wind
