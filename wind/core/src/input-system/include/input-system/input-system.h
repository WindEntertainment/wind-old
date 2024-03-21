#pragma once
#include "context.h"
#include "input-system/trigger.h"
#include "keys.h"
#include "utils/includes.h"
#include <vector>

namespace wind {

class InputSystem {
private:
  static InputSystemContext* context;

  static std::unordered_map<Key, Callbacks, KeyHash> keycodeTriggers;
  static std::map<std::string, Trigger*> groupedTriggers;

  static inline void groupedEventToCycle(Key keycode);

  static void addKeycodeTrigger(Keys bindings = {}, Callbacks callbacks = {});
  static void addKeycodeTrigger(Keys bindings = {}, Callback* callback = nullptr);
  static void addKeycodeTrigger(Key binding, Callbacks callbacks = {});
  static void addKeycodeTrigger(Key binding, Callback* callback = nullptr);

  static void addGroupedTrigger(std::string groupName, Keys bindings = {}, Callbacks callbacks = {});
  static void addGroupedTrigger(std::string groupName, Keys bindings = {}, Callback* callback = nullptr);
  static void addGroupedTrigger(std::string groupName, Key binding, Callbacks callbacks = {});
  static void addGroupedTrigger(std::string groupName, Key binding, Callback* callback = nullptr);

  static void removeKeycodeTrigger(Key binding, Callbacks callbacks);
  static void removeKeycodeTrigger(Callbacks callbacks);
  static void removeKeycodeTrigger(Key binding, Callback* callback);
  static void removeKeycodeTrigger(Callback* callback);

public:
  static void init(GLFWwindow* window);

  static void addTrigger(std::string groupName, Keys bindings = {}, Callbacks callbacks = {});
  static void addTrigger(std::string groupName, Keys bindings = {}, Callback* callback = nullptr);
  static void addTrigger(std::string groupName, Key binding, Callbacks callbacks = {});
  static void addTrigger(std::string groupName, Key binding, Callback* callback = nullptr);

  static void removeTrigger(std::string groupName);
  static void removeTrigger(std::set<std::string> groupNames);
};
} // namespace wind
