#include <asset-pipeline/asset-manager.h>
#include <renderer/particle.h>
#include <renderer/renderer.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

#include <asset-pipeline/pipes/default-pipe.h>
#include <asset-pipeline/pipes/img-pipe.h>
#include <asset-pipeline/pipes/shader-pipe.h>

int main() {
#ifndef NDEBUG
  spdlog::info("----Debug configuration!----");
#endif

  using namespace wind;

  using namespace wind::asset_pipeline;

  PipeRegister::regPipe(new ImagePipe());
  PipeRegister::regPipe(new ShaderPipe());
  PipeRegister::regPipe(new DefaultPipe());

  AssetManager::loadBundle("assets.bundle");

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
