#pragma once
#include "input-system/keys.h"
#include "set"
#include "utils/includes.h"

namespace wind {
struct MouseContext {
  double cursorX;
  double cursorY;
  double scrollX;
  double scrollY;

  std::set<KEYCODES> pressedButtons;
  std::set<KEYCODES> heldButtons;
  std::set<KEYCODES> releasedButtons;

  void addPressedButton(KEYCODES keycode);
  void addHeldButton(KEYCODES keycode);
  void addReleasedButton(KEYCODES keycode);

  void removePressedButton(KEYCODES keycode);
  void removeHeldButton(KEYCODES keycode);
  void removeReleasedButton(KEYCODES keycode);

  void moveCursor(double nextX, double nextY);
  void moveScroll(double nextX, double nextY);
};
} // namespace wind
