#include <glad/glad.h>

#include "input-system/context.h"
#include "input-system/keys.h"
#include "script-system/hostfxr.h"
#include "script-system/script-system.h"
#include "utils/includes.h"

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
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("----Debug configuration!----");
#endif

  using namespace wind;
  using namespace wind::assets;

  //=========Assets Pipeline===============//

  AssetManager::loadBundle("res/Ultralight.bundle");
  AssetManager::loadBundle("res/Main.bundle");

  //=========Input System==================//

  InputSystem::createTriggersFromFile("main/configs/triggers.yml");
  InputSystem::addTriggerCallbacks("ultralightMouseMove", &Ultralight::triggerMoveEvent);
  InputSystem::addTriggerCallbacks("ultralightMouseScroll", &Ultralight::triggerScrollEvent);
  InputSystem::addTriggerCallbacks("ultralightMousePress", &Ultralight::triggerMousePressEvent);
  InputSystem::addTriggerCallbacks("ultralightMouseRelease", &Ultralight::triggerMouseReleaseEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyPress", &Ultralight::triggerKeyPressEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyHold", &Ultralight::triggerKeyHoldEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyRelease", &Ultralight::triggerKeyReleaseEvent);
  InputSystem::addTriggerCallbacks("ultralightChars", &Ultralight::triggerCharEvent);

  //===============Window==================//

  Window::init([](Window::Config* self) {
    self->title = "Game";
    self->fullScreen = false;
    self->size = {800, 600};
    self->vSync = false;
  });

  //=============Ultralight================//

  Ultralight::init();
  const auto uiTexture = Ultralight::loadView("main/UI/dist/index.html", {800, 600});

  //============Script System==============//

  auto scriptsPath = fs::path("./res/Managed/");
  auto hostfxr = new ScriptSystemHostfxr();

  hostfxr->init(scriptsPath / "Scripts.runtimeconfig.json");

  ScriptSystem* scriptSystem = hostfxr->createScriptSystem(scriptsPath, scriptsPath / "Scripts.dll");

  scriptSystem->run("Scripts.Lib, Scripts", "HelloAgain", "from host!", 1);
  scriptSystem->run("Scripts.Lib, Scripts", "Hello", "from host!", 1);

  //=============Main loop=================//

  while (Window::update()) {
    Renderer::clear({1.f, 0.f, 0.f, 1});

    Ultralight::update();
    Ultralight::render();

    Renderer::drawTexture(uiTexture, {1, 1}, {0, 0, 0}, {0, 0, 0}, {800, 600, 1});

    Window::show();
  }

  hostfxr->stop();

  return EXIT_SUCCESS;
}
