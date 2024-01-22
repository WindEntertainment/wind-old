#include "ext_filesystem.h"
#include "ext_string.h"

namespace wind {

template <typename C, typename T>
concept Container = requires(C c, T t) {
    c.find(t);
    c.end();
};

template <typename C, typename T>
    requires Container<C, T>
bool contains(C _container, T _value) {
    auto it = _container.find(_value);
    return it != _container.end();
}

}  // namespace wind