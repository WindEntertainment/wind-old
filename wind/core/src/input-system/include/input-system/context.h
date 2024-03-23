#pragma once
#include "keyboard-context.h"
#include "mouse-context.h"
#include "utils/includes.h"

namespace wind {

struct InputSystemContext {
  KeyboardContext keyboardContext;
  MouseContext mouseContext;
};
} // namespace wind
