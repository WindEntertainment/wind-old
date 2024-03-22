#include "input-system/context.h"
#include "input-system/keys.h"
#include "script-system/hostfxr.h"
#include "script-system/script-system.h"
#include "utils/includes.h"
#include <GLFW/glfw3.h>

#include <functional>
#include <input-system/input-system.h>
#include <ostream>
#include <renderer/particle.h>
#include <renderer/renderer.h>
#include <spdlog/spdlog.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

using namespace wind;

int main(int argc, char* argv[]) {

  auto rootPath = fs::absolute(argv[0]).parent_path();
  auto scriptsPath = rootPath / "assets/scripts/bin/Release/";

  InputSystem::createTriggersFromFile(rootPath / "assets/configs/triggers.yml");

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

  InputSystem::addTrigger("ultralightMouseMove", {Key{KEYCODES::MOUSE_MOVE, KEY_ACTIONS::UNKNOWN}}, &Ultralight::triggerMoveEvent);
  InputSystem::addTrigger("ultralightMouseScroll", {Key{KEYCODES::MOUSE_SCROLL, KEY_ACTIONS::UNKNOWN}}, &Ultralight::triggerScrollEvent);
  InputSystem::addTrigger("ultralightMousePress", {Key{KEYCODES::ALL_MOUSE_KEYS, KEY_ACTIONS::PRESSED}}, &Ultralight::triggerMousePressEvent);
  InputSystem::addTrigger("ultralightMouseRelease", {Key{KEYCODES::ALL_MOUSE_KEYS, KEY_ACTIONS::RELEASED}}, &Ultralight::triggerMouseReleaseEvent);
  InputSystem::addTrigger("ultralightKeyPress", {Key{KEYCODES::ALL_KEYBOARD_KEYS, KEY_ACTIONS::PRESSED}}, &Ultralight::triggerKeyPressEvent);
  InputSystem::addTrigger("ultralightKeyHold", {Key{KEYCODES::ALL_KEYBOARD_KEYS, KEY_ACTIONS::HELD}}, &Ultralight::triggerKeyHoldEvent);
  InputSystem::addTrigger("ultralightKeyRelease", {Key{KEYCODES::ALL_KEYBOARD_KEYS, KEY_ACTIONS::RELEASED}}, &Ultralight::triggerKeyReleaseEvent);
  InputSystem::addTrigger("ultralightChars", {Key{KEYCODES::ALL_KEYBOARD_CHARS, KEY_ACTIONS::UNKNOWN}}, &Ultralight::triggerCharEvent);

  auto hostfxr = new ScriptSystemHostfxr();

  hostfxr->init(scriptsPath / "Scripts.runtimeconfig.json");

  ScriptSystem* scriptSystem = hostfxr->createScriptSystem(scriptsPath, scriptsPath / "Scripts.dll");

  scriptSystem->run("Scripts.Lib, Scripts", "HelloAgain", "from host!", 1);
  scriptSystem->run("Scripts.Lib, Scripts", "Hello", "from host!", 1);

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
