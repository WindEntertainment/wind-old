#include <cstdlib>
#include <utils/utils.h>
#include <window/window.h>

int main() {
    using namespace wind::math;

    wind::Window w([](wind::Window::Config *self) {
        self->title = "Hello, World!";
        self->fullscreen = false;
    });

    while (w.update()) {
        w.show();
    }

    return EXIT_SUCCESS;
}