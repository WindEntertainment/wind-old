#include "input-system/keyboard-context.h"
#include "input-system/keys.h"

namespace wind {
void KeyboardContext::setCodepoint(unsigned int codepoint) {
  this->codepoint = codepoint;
};
void KeyboardContext::addPressedKey(KEYCODES keycode) {
  pressedKeys.insert(keycode);
};
void KeyboardContext::addHeldKey(KEYCODES keycode) {
  heldKeys.insert(keycode);
};
void KeyboardContext::addReleasedKey(KEYCODES keycode) {
  releasedKeys.insert(keycode);
};

void KeyboardContext::removeCodepoint() {
  this->codepoint = 0;
};
void KeyboardContext::removePressedKey(KEYCODES keycode) {
  pressedKeys.erase(keycode);
};
void KeyboardContext::removeHeldKey(KEYCODES keycode) {
  heldKeys.erase(keycode);
};
void KeyboardContext::removeReleasedKey(KEYCODES keycode) {
  releasedKeys.erase(keycode);
};

} // namespace wind
