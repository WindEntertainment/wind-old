#include <renderer/particle.h>
#include <renderer/renderer.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

int main() {
  using namespace wind;

  Ultralight::init();
  Ultralight::initPlatform();
  Ultralight::createRenderer();
  UltralightViewManager::loadView("UI/dist/index.html");

  Window::init([](Window::Config* self) {
    self->title = "Game";
    self->fullScreen = false;
    self->size = {800, 600};
    self->vSync = false;
  });

  float scope = 1.f;
  vec2 camera = {};

  while (Window::update()) {
    if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
      Window::close();

    Renderer::clear({0.f, 0.f, 0.f, 1});

    Ultralight::updateLogic();
    Ultralight::renderOneFrame();

    // Renderer::drawRectangle({0, 0, 100, 100}, {0.f, 1.f, 0.f, 1.f});

    Renderer::updateCamera(camera);
    Renderer::setScope(scope);

    Window::show();
  }

  return EXIT_SUCCESS;
}
