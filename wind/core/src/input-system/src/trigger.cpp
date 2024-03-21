#include "input-system/trigger.h"
#include "input-system/keys.h"
#include "utils/includes.h"

namespace wind {
// void Trigger::addCallback(Callback* callback) {
//   callbacks.push_back(callback);
// }

// void Trigger::removeCallback(Callback* callback) {
//   auto it = std::find(callbacks.begin(), callbacks.end(), callback);
//   if (it != callbacks.end()) {
//     callbacks.erase(it);
//   }
// }

// void Trigger::addBinding(int key) {
//   bindings.push_back(key);
// }

// void Trigger::removeBinding(int key) {
//   bindings.erase(std::find(bindings.begin(), bindings.end(), key));
// }

// void Trigger::clearBindings() {
//   bindings.clear();
// }

// void Trigger::clearCallbacks() {
//   callbacks.clear();
// }

Trigger::Trigger(std::string name, const Keys bindings, const Callbacks callbacks)
    : name(name), bindings(bindings), callbacks(callbacks) {
}

} // namespace wind
