#include <utils/utils.h>
#include <window/events/keyboard.h>
#include <window/window.h>

int main() {
    using namespace wind::math;

    wind::Window w([](wind::Window::Config *self) {
        self->title = "Hello, World!";
        self->fullscreen = false;
    });

    while (w.update()) {
        if (wind::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            w.close();

        w.show();
        std::cout << w.getFPS() << "\n";
    }

    return EXIT_SUCCESS;
}