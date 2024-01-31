// clang-format off
#include <renderer/renderer.h>
#include <window/window.h>
#include <utils/utils.h>
// clang-format on

int main() {
    using namespace wind;

    Window::init([](Window::Config* self) {
        self->title = "Hello, World!";
        self->fullScreen = false;
    });

    renderer::Renderer* renderer = new renderer::Renderer();
    renderer::Camera camera{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};

    while (Window::update()) {
        if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            Window::close();

        renderer->clear();
        Window::show();
    }

    return EXIT_SUCCESS;
}