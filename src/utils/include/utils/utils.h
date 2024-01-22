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

class Stopwatch {
public:
    Stopwatch(const std::string& message) : message(message) {
        start_time = std::chrono::high_resolution_clock::now();
    }

    ~Stopwatch() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        spdlog::info("{} took {} milliseconds", message, duration.count());
    }

private:
    std::string message;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

}  // namespace wind