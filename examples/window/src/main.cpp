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

    while (Window::update()) {
        if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            Window::close();

        Renderer::drawRectangle({0, 0, 0.5f, 0.5f}, {0, 1, 0, 1});
        Window::show();
    }

    return EXIT_SUCCESS;
}