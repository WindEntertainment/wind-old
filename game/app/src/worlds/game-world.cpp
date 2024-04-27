#include "game/worlds/game-world.hpp"

#include "game/components/enemy.hpp"
#include "game/components/moveable.hpp"
#include "game/components/player.hpp"
#include "game/components/renderable.hpp"
#include "game/components/transform.hpp"

namespace game {

void GameWorld::load() {
  InputSystem::createTriggersFromFile("main/configs/triggers.yml");

  // clang-format off

  auto background = world.createEntity();
  world.attachComponent(background, Transform{.scale = {800, 600}});
  world.attachComponent(background, Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/background.png")
  });

  auto player = world.createEntity();
  world.attachComponent(player, Player{});
  world.attachComponent(player, Transform{.scale = {128, 128}});
  world.attachComponent(player, Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/player.png")
  });

  auto enemy = world.createEntity();
  world.attachComponent(enemy, Enemy{});
  world.attachComponent(enemy, Transform{
    .position = {0, -300, 0},
    .scale = {128, 128}
  });
  world.attachComponent(enemy, Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/enemy.png")
  });
  world.attachComponent(enemy, Moveable{
    .velocity = { 0.1f, 0.f, 0.f }
  });

  // clang-format on
}

void GameWorld::update() {
  world.forEachWith<Moveable, Transform>([](const auto& moveable, auto& transform) {
    transform.position += moveable.velocity;
  });

  Renderer::clear({0.f, 0.f, 0.f, 1});

  world.forEachWith<Renderable, Transform>([](const auto& renderable, const auto& transform) {
    Renderer::drawTexture(renderable.texture, {1, 1}, transform.position, {0, 0, 0}, transform.scale);
  });
}

void GameWorld::unload() {
}

} // namespace game