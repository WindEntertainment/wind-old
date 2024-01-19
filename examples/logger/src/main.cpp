#include <wind.h>

class ClassInvalidCase {};

int main() {
    int testVar = 3;

    spdlog::info("Hi, World! {}", testVar);
    return 0;
}