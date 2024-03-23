#include "input-system/input-system.h"

#include "input-system/context.h"
#include "input-system/keys.h"
#include "input-system/trigger.h"
#include "utils/includes.h"
#include "utils/utils.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

namespace wind {

void InputSystem::addKeycodeTrigger(Keys bindings) {
  std::for_each(bindings.begin(), bindings.end(), [](Key binding) {
    keycodeTriggers[binding] = std::set<Callback*>();
  });
};

void InputSystem::addKeycodeTrigger(Key binding) {
  keycodeTriggers[binding] = std::set<Callback*>();
};

void InputSystem::addKeycodeTrigger(Keys bindings, Callbacks callbacks) {
  std::for_each(bindings.begin(), bindings.end(), [&callbacks](Key binding) {
    addKeycodeTrigger(binding, callbacks);
  });
}

void InputSystem::addKeycodeTrigger(Keys bindings, Callback* callback) {
  std::for_each(bindings.begin(), bindings.end(), [&callback](Key binding) {
    addKeycodeTrigger(binding, callback);
  });
}

void InputSystem::addKeycodeTrigger(Key binding, Callbacks callbacks) {
  if (keycodeTriggers.contains(binding)) {
    keycodeTriggers.insert(std::make_pair(binding, callbacks));
  } else {
    keycodeTriggers[binding].insert(callbacks.begin(), callbacks.end());
  };
}

void InputSystem::addKeycodeTrigger(Key binding, Callback* callback) {
  if (keycodeTriggers.contains(binding)) {
    keycodeTriggers.insert(std::make_pair(binding, std::set{callback}));
  } else {
    keycodeTriggers[binding].insert({callback});
  };
}

//

void InputSystem::addKeycodeTriggerBindings(std::string groupName, Key binding) {
  if (!groupedTriggers.contains(groupName))
    return;

  auto trigger = groupedTriggers[groupName];
  addKeycodeTrigger(binding, trigger->callbacks);
};

void InputSystem::addKeycodeTriggerBindings(std::string groupName, Keys bindings) {
  if (!groupedTriggers.contains(groupName))
    return;

  auto trigger = groupedTriggers[groupName];
  std::for_each(bindings.begin(), bindings.end(), [&trigger](auto binding) {
    addKeycodeTrigger(binding, trigger->callbacks);
  });
};

//

void InputSystem::addKeycodeTriggerCallbacks(std::string groupName, Callback* callback) {
  if (!groupedTriggers.contains(groupName))
    return;

  auto trigger = groupedTriggers[groupName];

  std::for_each(trigger->bindings.begin(), trigger->bindings.end(), [&trigger, &callback](auto binding) {
    if (!keycodeTriggers.contains(binding))
      return;

    keycodeTriggers[binding].insert(callback);
  });
};

void InputSystem::addKeycodeTriggerCallbacks(std::string groupName, Callbacks callbacks) {
  if (!groupedTriggers.contains(groupName))
    return;

  auto trigger = groupedTriggers[groupName];

  std::for_each(trigger->bindings.begin(), trigger->bindings.end(), [&trigger, &callbacks](auto binding) {
    if (!keycodeTriggers.contains(binding))
      return;

    keycodeTriggers[binding].insert(callbacks.begin(), callbacks.end());
  });
};

//

void InputSystem::removeKeycodeTrigger(Key binding, Callbacks callbacks) {
  std::for_each(callbacks.begin(), callbacks.end(), [&binding](Callback* callback) {
    removeKeycodeTrigger(binding, callback);
  });
}

void InputSystem::removeKeycodeTrigger(Callbacks callbacks) {
  std::for_each(keycodeTriggers.begin(), keycodeTriggers.end(), [&callbacks](auto pair) {
    removeKeycodeTrigger(pair.first, callbacks);
  });
}

void InputSystem::removeKeycodeTrigger(Key binding, Callback* callback) {
  auto it = std::find(keycodeTriggers[binding].begin(), keycodeTriggers[binding].end(), callback);
  if (it != keycodeTriggers[binding].end()) {
    keycodeTriggers[binding].erase(it);
  }
}

void InputSystem::removeKeycodeTrigger(Callback* callback) {
  std::for_each(keycodeTriggers.begin(), keycodeTriggers.end(), [&callback](auto pair) {
    removeKeycodeTrigger(pair.first, callback);
  });
}
} // namespace wind
