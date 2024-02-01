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

        Renderer::clear({0, 0, 0, 1});
        Renderer::drawRectangle({100, 100, 100, 100}, {0.8f, 0.8f, 0.8f, 1});
        Renderer::drawCircle({400, 300}, 50, {0.f, 0.5f, 0.f, 1});
        Window::show();
    }

    return EXIT_SUCCESS;
}