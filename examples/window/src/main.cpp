// clang-format off
#include <renderer/renderer.h>
#include <window/window.h>
#include <utils/utils.h>
// clang-format on

int main() {
    using namespace wind::math;

    wind::Window w([](wind::Window::Config* self) {
        self->title = "Hello, World!";
        self->fullscreen = false;
    });

    wind::renderer::Renderer* renderer = new wind::renderer::Renderer();
    wind::renderer::Camera camera{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};

    while (w.update()) {
        if (wind::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            w.close();

        renderer->clear();
        w.show();
    }

    return EXIT_SUCCESS;
}