#pragma once
#include "context.h"
#include "input-system/keys.h"
#include <functional>
#include <iostream>
#include <map>
#include <set>

namespace wind {
using Callback = void(InputSystemContext*);
using Callbacks = std::set<Callback*>;

struct Trigger {
  std::string name;
  Keys bindings;
  Callbacks callbacks;

  Trigger(std::string name, const Keys bindings = {}, const Callbacks callbacks = {});
};

} // namespace wind
