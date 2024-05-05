#include "game/worlds.hpp"

#include "game/components/enemy.hpp"
#include "game/components/moveable.hpp"
#include "game/components/player.hpp"
#include "game/components/renderable.hpp"
#include "game/components/transform.hpp"

#include "game/systems/controll-system.hpp"
#include "game/systems/following-system.hpp"
#include "game/systems/move-system.hpp"
#include "game/systems/render-system.hpp"

namespace game {

World* loadGameWorld() {
  World* world = new World();

  // clang-format off

  auto background = world->createEntity();
  world->attachComponent(background, Transform{.scale = {800, 600}});
  world->attachComponent(background, Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/background.png")
  });

  auto player = world->createEntity();
  world->attachComponent(player, Player{});
  world->attachComponent(player, Transform{.scale = {128, 128}});
  world->attachComponent(player, Moveable{});
  world->attachComponent(player, Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/player.png")
  });

  auto enemy = world->createEntity();
  world->attachComponent(enemy, Enemy{
    .target = player
  });
  world->attachComponent(enemy, Moveable{});
  world->attachComponent(enemy, Transform{
    .position = {0, -300, 0},
    .scale = {128, 128}
  });
  world->attachComponent(enemy, Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/enemy.png")
  });

  world->addSystem(std::make_unique<RenderSystem>());
  world->addSystem(std::make_unique<MoveSystem>());
  world->addSystem(std::make_unique<ControllSystem>());
  world->addSystem(std::make_unique<FollowingSystem>());

  // clang-format on

  return world;
}

} // namespace game