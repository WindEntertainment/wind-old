#pragma once
#include "context.h"
#include "input-system/trigger.h"
#include "keys.h"
#include "utils/includes.h"
#include <GLFW/glfw3.h>
#include <vector>

namespace wind {

class InputSystem {
public:
  static void init(GLFWwindow* window);

  static void createTriggersFromFile(std::filesystem::path path);

  static void addTrigger(std::string groupName, Keys bindings, Callbacks callbacks);
  static void addTrigger(std::string groupName, Keys bindings, Callback* callback);
  static void addTrigger(std::string groupName, Key binding, Callbacks callbacks);
  static void addTrigger(std::string groupName, Key binding, Callback* callback);
  static void addTrigger(std::string groupName, Key binding);
  static void addTrigger(std::string groupName, Keys bindings);
  static void addTrigger(std::string groupName);

  static void addTriggerBindings(std::string groupName, Keys bindings);
  static void addTriggerBindings(std::string groupName, Key binding);

  static void addTriggerCallbacks(std::string groupName, Callbacks callbacks);
  static void addTriggerCallbacks(std::string groupName, Callback callback);

  static void removeTriggerBindings(std::string groupName, Keys bindings);
  static void removeTriggerBindings(std::string groupName, Key binding);

  static void removeTriggerCallbacks(std::string groupName, Callbacks callbacks);
  static void removeTriggerCallbacks(std::string groupName, Callback* callback);

  static void removeTrigger(std::string groupName);
  static void removeTrigger(std::set<std::string> groupNames);

  static std::unordered_map<Key, Callbacks, KeyHash> keycodeTriggers;
  static std::map<std::string, Trigger*> groupedTriggers;

private:
  static InputSystemContext* context;

  static inline void groupedEventToCycle(Key keycode);

  static void addKeycodeTrigger(Keys bindings, Callbacks callbacks);
  static void addKeycodeTrigger(Keys bindings, Callback* callback);
  static void addKeycodeTrigger(Key binding, Callbacks callbacks);
  static void addKeycodeTrigger(Key binding, Callback* callback);
  static void addKeycodeTrigger(Keys bindings);
  static void addKeycodeTrigger(Key binding);

  static void addKeycodeTriggerBindings(std::string groupName, Key binding);
  static void addKeycodeTriggerBindings(std::string groupName, Keys bindings);

  static void addKeycodeTriggerCallbacks(std::string groupName, Callback* callback);
  static void addKeycodeTriggerCallbacks(std::string groupName, Callbacks callbacks);

  static void addGroupedTrigger(std::string groupName, Keys bindings, Callbacks callbacks);
  static void addGroupedTrigger(std::string groupName, Keys bindings, Callback* callback);
  static void addGroupedTrigger(std::string groupName, Key binding, Callbacks callbacks);
  static void addGroupedTrigger(std::string groupName, Key binding, Callback* callback);
  static void addGroupedTrigger(std::string groupName, Keys bindings);
  static void addGroupedTrigger(std::string groupName, Key binding);
  static void addGroupedTrigger(std::string groupName);

  static void addGroupedTriggerBindings(std::string groupName, Key binding);
  static void addGroupedTriggerBindings(std::string groupName, Keys bindings);

  static void addGroupedTriggerCallbacks(std::string groupName, Callback* callback);
  static void addGroupedTriggerCallbacks(std::string groupName, Callbacks callbacks);

  static void removeKeycodeTrigger(Key binding, Callbacks callbacks);
  static void removeKeycodeTrigger(Callbacks callbacks);
  static void removeKeycodeTrigger(Key binding, Callback* callback);
  static void removeKeycodeTrigger(Callback* callback);
};
} // namespace wind
