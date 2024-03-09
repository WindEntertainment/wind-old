// clang-format off
#include <renderer/renderer.h>
#include <renderer/particle.h>
#include <window/window.h>
#include <utils/utils.h>
// clang-format on

int main() {
    using namespace wind;

    Window::init([](Window::Config* self) {
        self->title = "Game";
        self->fullScreen = false;
        self->size = {800, 600};
        self->vSync = false;
    });

    while (Window::update()) {
        if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            Window::close();

        Renderer::clear({0.1f, 0.1f, 0.1f, 1});
        Window::show();
    }

    return EXIT_SUCCESS;
}