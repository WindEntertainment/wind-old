#include <renderer/particle.h>
#include <renderer/renderer.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

int main() {
  using namespace wind;

  Window::init([](Window::Config* self) {
    self->title = "Game";
    self->fullScreen = false;
    self->size = {800, 600};
    self->vSync = false;
  });


  Ultralight::init();
  const auto uiTexture = Ultralight::loadView("UI/dist/index.html", {800, 600});

  float scope = 1.f;
  glm::vec2 camera = {};

  while (Window::update()) {
    if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
      Window::close();

    Renderer::clear({1.f, 0.f, 0.f, 1});

    Ultralight::update();
    Ultralight::render();

    Renderer::drawTexture(uiTexture, {1, 1}, {0, 0, 0}, {0, 0, 0}, {800, 600, 1});

    Renderer::updateCamera(camera);
    Renderer::setScope(scope);

    Window::show();
  }

  return EXIT_SUCCESS;
}
