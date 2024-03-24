#include "input-system/context.h"
#include "input-system/keys.h"
#include "script-system/hostfxr.h"
#include "script-system/script-system.h"
#include "utils/includes.h"
#include <GLFW/glfw3.h>

#include <algorithm>
#include <asset-manager/asset-manager.hpp>
#include <functional>
#include <input-system/input-system.h>
#include <ostream>
#include <renderer/particle.h>
#include <renderer/renderer.h>
#include <spdlog/spdlog.h>
#include <utils/includes.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
            #include <window/window.h>

int main(int argc, char** argv) {
#ifndef NDEBUG
#define SPDLOG
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("----Debug configuration!----");
#endif

  using namespace wind;

  using namespace wind::asset_pipeline;

  PipeRegister::regPipe(new DefaultPipe());
  PipeRegister::regPipe(new ShaderPipe());
  PipeRegister::regPipe(new ImagePipe());

  AssetManager::loadBundle("assets.bundle");

  auto rootPath = fs::absolute(argv[0]).parent_path();
  auto scriptsPath = rootPath / "assets/scripts/bin/Release/";

  InputSystem::createTriggersFromFile("configs/triggers.yml");

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

  InputSystem::addTriggerCallbacks("ultralightMouseMove", &Ultralight::triggerMoveEvent);
  InputSystem::addTriggerCallbacks("ultralightMouseScroll", &Ultralight::triggerScrollEvent);
  InputSystem::addTriggerCallbacks("ultralightMousePress", &Ultralight::triggerMousePressEvent);
  InputSystem::addTriggerCallbacks("ultralightMouseRelease", &Ultralight::triggerMouseReleaseEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyPress", &Ultralight::triggerKeyPressEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyHold", &Ultralight::triggerKeyHoldEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyRelease", &Ultralight::triggerKeyReleaseEvent);
  InputSystem::addTriggerCallbacks("ultralightChars", &Ultralight::triggerCharEvent);

  // auto hostfxr = new ScriptSystemHostfxr();

  // hostfxr->init(scriptsPath / "Scripts.runtimeconfig.json");

  // ScriptSystem* scriptSystem = hostfxr->createScriptSystem(scriptsPath, scriptsPath / "Scripts.dll");

  // scriptSystem->run("Scripts.Lib, Scripts", "HelloAgain", "from host!", 1);
  // scriptSystem->run("Scripts.Lib, Scripts", "Hello", "from host!", 1);

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

  // hostfxr->stop();

  return EXIT_SUCCESS;
}
