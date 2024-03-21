#include "input-system/context.h"
#include "input-system/keys.h"
#include "utils/includes.h"
#include <GLFW/glfw3.h>

#include <functional>
#include <input-system/input-system.h>
#include <ostream>
#include <renderer/particle.h>
#include <renderer/renderer.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

using namespace wind;

int main() {

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
