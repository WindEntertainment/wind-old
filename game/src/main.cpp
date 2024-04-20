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

  //============= Load textures =================//

  auto playerImg = AssetManager::getAsset<Image>("main/art/player.png");
  auto playerTex = new Texture(playerImg->pixels, playerImg->size);
  delete playerImg;

  auto enemyImg = AssetManager::getAsset<Image>("main/art/enemy.png");
  auto enemyTex = new Texture(enemyImg->pixels, enemyImg->size);
  delete enemyImg;

  auto backgroundImg = AssetManager::getAsset<Image>("main/art/background.png");
  auto backgroundTex = new Texture(backgroundImg->pixels, backgroundImg->size);
  delete backgroundImg;

  //============= Components ======================//
  struct Player {
    int a;
  };

  struct Transform {
    glm::vec3 position = {0.1f, 0.1f, 0};
    glm::vec2 rotation = {};
    glm::vec2 scale = {1, 1};
  };

  struct Renderable {
    Texture* texture;
  };

  struct Enemy {
    int b;
    // Transform* target;
  };

  //============= Generate world =================//

  World world;

  auto background = world.createEntity();
  world.attachComponent(background, Transform{.scale = {800, 600}});
  world.attachComponent(background, Renderable{backgroundTex});

  auto player = world.createEntity();
  world.attachComponent(player, Player{});
  world.attachComponent(player, Transform{.scale = {128, 128}});
  world.attachComponent(player, Renderable{playerTex});

  auto enemy = world.createEntity();
  world.attachComponent(enemy, Enemy{}); // Enemy{.target = &world.getComponent<Transform>(player)});
  world.attachComponent(enemy, Transform{.position = {0, -300, 0}, .scale = {128, 128}});
  world.attachComponent(enemy, Renderable{enemyTex});

  //=============Main loop=================//

  glm::vec3 velocity;

  InputSystem::addTriggerCallbacks("playerMoveUpPressed", [&velocity](InputSystemContext* context) {
    velocity.y = 1;
  });
  InputSystem::addTriggerCallbacks("playerMoveDownPressed", [&velocity](InputSystemContext* context) {
    velocity.y = -1;
  });
  InputSystem::addTriggerCallbacks("playerMoveLeftPressed", [&velocity](InputSystemContext* context) {
    velocity.x = -1;
  });
  InputSystem::addTriggerCallbacks("playerMoveRightPressed", [&velocity](InputSystemContext* context) {
    velocity.x = 1;
  });

  InputSystem::addTriggerCallbacks("playerMoveUpReleased", [&velocity](InputSystemContext* context) {
    velocity.y = velocity.y == 1 ? 0 : velocity.y;
  });
  InputSystem::addTriggerCallbacks("playerMoveDownReleased", [&velocity](InputSystemContext* context) {
    velocity.y = velocity.y == -1 ? 0 : velocity.y;
  });
  InputSystem::addTriggerCallbacks("playerMoveLeftReleased", [&velocity](InputSystemContext* context) {
    velocity.x = velocity.x == -1 ? 0 : velocity.x;
  });
  InputSystem::addTriggerCallbacks("playerMoveRightReleased", [&velocity](InputSystemContext* context) {
    velocity.x = velocity.x == 1 ? 0 : velocity.x;
  });

  while (Window::update()) {

    world.forEachWith<Player, Transform>([&velocity](const auto& player, auto& transform) {
      transform.position += velocity;
    });

    world.forEachWith<Enemy, Transform>([&world, &player](const auto& enemy, auto& transform) {
      // glm::vec2 velocity = glm::normalize(enemy.target->position - transform.position);
      // spdlog::info("enemy target position: [x: {}, y: {}]", enemy.target->position.x, enemy.target->position.y);
      // transform.position += glm::vec3{velocity.x, velocity.y, 0} / 2.f;

      glm::vec2 velocity = glm::normalize(world.getComponent<Transform>(player).position - transform.position);
      // spdlog::info("enemy target position: [x: {}, y: {}]", enemy.target->position.x, enemy.target->position.y);
      transform.position += glm::vec3{velocity.x, velocity.y, 0} / 2.f;
    });

    Renderer::clear({0.f, 0.f, 0.f, 1});

    world.forEachWith<Renderable, Transform>([](const auto& renderable, const auto& transform) {
      Renderer::drawTexture(renderable.texture, {1, 1}, transform.position, {0, 0, 0}, transform.scale);
    });

    Ultralight::update();
    Ultralight::render();
    // Renderer::drawTexture(uiTexture, {1, 1}, {0, 0, 0}, {0, 0, 0}, {800, 600, 1});

    Window::show();
  }

  delete playerTex;
  Window::destroy();

  return EXIT_SUCCESS;
}