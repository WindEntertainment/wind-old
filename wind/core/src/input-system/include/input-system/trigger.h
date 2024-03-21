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

  // void addCallback(Callback* callback);
  // void removeCallback(Callback* callback);
  // void addBinding(int key);
  // void removeBinding(int key);
  // void clearBindings();
  // void clearCallbacks();

  Trigger(std::string name, const Keys bindings = {}, const Callbacks callbacks = {});
};

} // namespace wind
