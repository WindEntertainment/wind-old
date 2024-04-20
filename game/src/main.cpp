#include <glad/glad.h>

#include "input-system/context.h"
#include "input-system/keys.h"
#include "script-system/hostfxr.h"
#include "script-system/script-system.h"
#include "utils/includes.h"

#include <algorithm>
#include <asset-manager/asset-manager.hpp>
#include <breeze/breeze.hpp>
#include <functional>
#include <input-system/input-system.h>
#include <ostream>
#include <renderer/particle.hpp>
#include <renderer/renderer.hpp>
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
    self->vSync = true;
  });

  //=============Ultralight================//

  Ultralight::init();

  const auto uiTexture = Ultralight::loadView("main/UI/dist/index.html", {800, 600});

  //============= ECS =================//

  auto player_img = AssetManager::getAsset<Image>("main/art/player.png");
  auto player = new Texture(player_img->pixels, player_img->size);

  struct Transform {
    glm::vec3 position = {};
    glm::vec2 rotation = {};
    glm::vec2 scale = {1, 1};
  };

  struct Renderable {
    Texture* texture;
  };

  World world;

  for (int i = 0; i < 100; ++i) {
    auto entity = world.createEntity();
    world.attachComponent(entity, Transform{{-400 + rand() % 800, -300 + rand() % 600, 0}});
    world.attachComponent(entity, Renderable{player});
  }

  auto filter = world.createFilter<Renderable, Transform>();

  //=============Main loop=================//

  while (Window::update()) {
    Renderer::clear({0.f, 0.f, 0.f, 1});

    Ultralight::update();
    Ultralight::render();

    for (auto [renderable, transform] : *filter) {
      Renderer::drawTexture(renderable->texture, {1, 1}, transform->position, {0, 0, 0}, {64, 64, 1});
      transform->position.x += (-5 + rand() % 11) / 5.f;
      transform->position.y += (-5 + rand() % 11) / 5.f;
    }

    // Renderer::drawTexture(uiTexture, {1, 1}, {0, 0, 0}, {0, 0, 0}, {800, 600, 1});

    Window::show();
  }

  // hostfxr->stop();

  delete player_img;
  delete player;
  Window::destroy();

  return EXIT_SUCCESS;
}
