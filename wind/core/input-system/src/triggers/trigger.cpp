#include "input-system/trigger.h"
#include "input-system/keys.h"
#include "utils/includes.h"

namespace wind {
Trigger::Trigger(std::string name, const Keys bindings, const Callbacks callbacks)
    : name(name), bindings(bindings), callbacks(callbacks) {
}

} // namespace wind
