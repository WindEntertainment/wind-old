#include "input-system/input-system.h"

#include "input-system/context.h"
#include "input-system/keys.h"
#include "input-system/trigger.h"
#include "utils/includes.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

namespace wind {
std::unordered_map<Key, Callbacks, KeyHash> InputSystem::keycodeTriggers;
std::map<std::string, Trigger*> InputSystem::groupedTriggers;

InputSystemContext* InputSystem::context = new InputSystemContext();

inline void InputSystem::groupedEventToCycle(Key keycode) {
  if (keycodeTriggers.contains(keycode)) {
    std::for_each(keycodeTriggers[keycode].begin(), keycodeTriggers[keycode].end(), [](Callback* callback) { callback(context); });
  };
}

void InputSystem::init(GLFWwindow* window) {
  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto mappedKey = mapGlfwKeyboardCodeToKey(key, action);

    switch (mappedKey.action) {
    case KEY_ACTIONS::PRESSED:
      context->keyboardContext.addPressedKey(mappedKey.keycode);
      context->keyboardContext.removeHeldKey(mappedKey.keycode);
      context->keyboardContext.removeReleasedKey(mappedKey.keycode);
      break;

    case KEY_ACTIONS::HELD:
      context->keyboardContext.addHeldKey(mappedKey.keycode);
      context->keyboardContext.removePressedKey(mappedKey.keycode);
      context->keyboardContext.removeReleasedKey(mappedKey.keycode);
      break;

    case KEY_ACTIONS::RELEASED:
      context->keyboardContext.addReleasedKey(mappedKey.keycode);
      context->keyboardContext.removePressedKey(mappedKey.keycode);
      context->keyboardContext.removeHeldKey(mappedKey.keycode);
      break;

    default:
      break;
    }

    groupedEventToCycle(mappedKey);
    groupedEventToCycle(Key{KEYCODES::ALL_KEYBOARD_KEYS, mappedKey.action});
    groupedEventToCycle(Key{KEYCODES::ALL_EVENTS, mappedKey.action});
  });

  glfwSetCursorPosCallback(window,
    [](GLFWwindow*, double x, double y) {
      context->mouseContext.moveCursor(x, y);

      groupedEventToCycle(Key{KEYCODES::MOUSE_MOVE, KEY_ACTIONS::UNKNOWN});
      groupedEventToCycle(Key{KEYCODES::ALL_MOUSE_EVENTS, KEY_ACTIONS::UNKNOWN});
      groupedEventToCycle(Key{KEYCODES::ALL_EVENTS, KEY_ACTIONS::UNKNOWN});
    });

  glfwSetMouseButtonCallback(window,
    [](GLFWwindow*, int button, int action, int mods) {
      auto mappedButton = mapGlfwMouseCodeToKey(button, action);

      switch (mappedButton.action) {
      case KEY_ACTIONS::PRESSED:
        context->mouseContext.addPressedButton(mappedButton.keycode);
        context->mouseContext.removeHeldButton(mappedButton.keycode);
        context->mouseContext.removeReleasedButton(mappedButton.keycode);
        break;

      case KEY_ACTIONS::HELD:
        context->mouseContext.addHeldButton(mappedButton.keycode);
        context->mouseContext.removePressedButton(mappedButton.keycode);
        context->mouseContext.removeReleasedButton(mappedButton.keycode);
        break;

      case KEY_ACTIONS::RELEASED:
        context->mouseContext.addReleasedButton(mappedButton.keycode);
        context->mouseContext.removePressedButton(mappedButton.keycode);
        context->mouseContext.removeHeldButton(mappedButton.keycode);
        break;

      default:
        break;
      }

      groupedEventToCycle(mappedButton);
      groupedEventToCycle(Key{KEYCODES::ALL_MOUSE_KEYS, mappedButton.action});
      groupedEventToCycle(Key{KEYCODES::ALL_MOUSE_EVENTS, mappedButton.action});
      groupedEventToCycle(Key{KEYCODES::ALL_EVENTS, mappedButton.action});
    });

  glfwSetScrollCallback(window,
    [](GLFWwindow*, double x, double y) {
      if (y > 0) {
        groupedEventToCycle(Key{KEYCODES::MOUSE_SCROLL_DOWN, KEY_ACTIONS::UNKNOWN});
      }

      if (y < 0) {
        groupedEventToCycle(Key{KEYCODES::MOUSE_SCROLL_UP, KEY_ACTIONS::UNKNOWN});
      }

      context->mouseContext.moveScroll(x, y);

      groupedEventToCycle(Key{KEYCODES::MOUSE_SCROLL, KEY_ACTIONS::UNKNOWN});

      groupedEventToCycle(Key{KEYCODES::ALL_MOUSE_EVENTS, KEY_ACTIONS::UNKNOWN});
      groupedEventToCycle(Key{KEYCODES::ALL_EVENTS, KEY_ACTIONS::UNKNOWN});

      context->mouseContext.moveScroll(0, 0);
    });

  glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
    context->keyboardContext.setCodepoint(codepoint);
    groupedEventToCycle(Key{KEYCODES::ALL_KEYBOARD_CHARS, KEY_ACTIONS::UNKNOWN});
    context->keyboardContext.removeCodepoint();
  });
}

//

void InputSystem::createTriggersFromFile(std::filesystem::path path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    spdlog::error("Failed to open the file {}", path.string());
    return;
  }

  YAML::Node config = YAML::Load(file);

  file.close();

  if (!config["triggers"] || !config["triggers"].IsSequence()) {
    spdlog::error("Can not load actions from file {}. The 'actions' key is either missing or not a sequence.", path.string());
    return;
  }

  for (const auto& triggerNode : config["triggers"]) {
    std::string name = triggerNode["name"].as<std::string>();
    Keys bindings;

    for (const auto& bindingNode : triggerNode["bindings"]) {
      auto key = mapStringToKeycode(bindingNode["key"].as<std::string>());
      auto actionType = mapStringToKeyAction(bindingNode["action"].as<std::string>());

      bindings.insert(Key{key, actionType});
    }

    addTrigger(name, bindings);

    spdlog::info("Loaded action {}", name);
  }
}

//

void InputSystem::addTrigger(std::string groupName, Keys bindings, Callbacks callbacks) {
  addGroupedTrigger(groupName, bindings, callbacks);
  addKeycodeTrigger(bindings, callbacks);
}

void InputSystem::addTrigger(std::string groupName, Keys bindings, Callback* callback) {
  addGroupedTrigger(groupName, bindings, callback);
  addKeycodeTrigger(bindings, callback);
}

void InputSystem::addTrigger(std::string groupName, Key binding, Callbacks callbacks) {
  addGroupedTrigger(groupName, binding, callbacks);
  addKeycodeTrigger(binding, callbacks);
}

void InputSystem::addTrigger(std::string groupName, Key binding, Callback* callback) {
  addGroupedTrigger(groupName, binding, callback);
  addKeycodeTrigger(binding, callback);
}

void InputSystem::addTrigger(std::string groupName, Keys bindings) {
  addGroupedTrigger(groupName, bindings, {});
  addKeycodeTrigger(bindings, {});
}

void InputSystem::addTrigger(std::string groupName, Key binding) {
  addGroupedTrigger(groupName, binding, {});
  addKeycodeTrigger(binding, {});
}

void InputSystem::addTrigger(std::string groupName) {
  addGroupedTrigger(groupName);
}

//

void InputSystem::addGroupedTrigger(std::string groupName, Keys bindings, Callbacks callbacks) {
  if (groupedTriggers.contains(groupName)) {
    groupedTriggers[groupName]->callbacks.insert(callbacks.begin(), callbacks.end());
    groupedTriggers[groupName]->bindings.insert(bindings.begin(), bindings.end());
  } else {
    groupedTriggers.insert(std::make_pair(groupName, new Trigger(groupName, bindings, callbacks)));
  }
}

void InputSystem::addGroupedTrigger(std::string groupName, Keys bindings, Callback* callback) {
  if (groupedTriggers.contains(groupName)) {
    groupedTriggers[groupName]->callbacks.insert(callback);
    groupedTriggers[groupName]->bindings.insert(bindings.begin(), bindings.end());
  } else {
    groupedTriggers.insert(std::make_pair(groupName, new Trigger(groupName, bindings, {callback})));
  }
}

void InputSystem::addGroupedTrigger(std::string groupName, Key binding, Callbacks callbacks) {
  if (groupedTriggers.contains(groupName)) {
    groupedTriggers[groupName]->callbacks.insert(callbacks.begin(), callbacks.end());
    groupedTriggers[groupName]->bindings.insert(binding);
  } else {
    groupedTriggers.insert(std::make_pair(groupName, new Trigger(groupName, {binding}, callbacks)));
  }
}

void InputSystem::addGroupedTrigger(std::string groupName, Key binding, Callback* callback) {
  if (groupedTriggers.contains(groupName)) {
    groupedTriggers[groupName]->callbacks.insert(callback);
    groupedTriggers[groupName]->bindings.insert(binding);
  } else {
    groupedTriggers.insert(std::make_pair(groupName, new Trigger(groupName, {binding}, {callback})));
  }
}

void InputSystem::addGroupedTrigger(std::string groupName) {
  if (!groupedTriggers.contains(groupName)) {
    groupedTriggers.insert(std::make_pair(groupName, new Trigger(groupName, {}, {})));
  }
}

//

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
// , bool forced
void InputSystem::removeTrigger(std::string groupName) {
  if (groupedTriggers.contains(groupName)) {
    std::for_each(
      groupedTriggers[groupName]->bindings.begin(),
      groupedTriggers[groupName]->bindings.end(),
      [&groupName](auto binding) { removeKeycodeTrigger(binding, groupedTriggers[groupName]->callbacks); });

    groupedTriggers.erase(groupName);
  };
};
// , bool forced
void InputSystem::removeTrigger(std::set<std::string> groupNames) {
  std::for_each(
    groupNames.begin(),
    groupNames.end(),
    [](auto groupName) { removeTrigger(groupName); });
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
