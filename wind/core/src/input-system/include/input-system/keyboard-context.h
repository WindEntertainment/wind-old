#pragma once
#include "input-system/keys.h"
#include "set"
#include "utils/includes.h"

namespace wind {
struct KeyboardContext {
  std::set<KEYCODES> pressedKeys;
  std::set<KEYCODES> heldKeys;
  std::set<KEYCODES> releasedKeys;
  unsigned int codepoint;

  void setCodepoint(unsigned int codepoint);
  void addPressedKey(KEYCODES key);
  void addHeldKey(KEYCODES key);
  void addReleasedKey(KEYCODES key);

  void removeCodepoint();
  void removePressedKey(KEYCODES key);
  void removeHeldKey(KEYCODES key);
  void removeReleasedKey(KEYCODES key);
};
} // namespace wind
