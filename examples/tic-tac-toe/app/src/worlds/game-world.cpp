#include "game/worlds.hpp"

#include "game/components/renderable.hpp"
#include "game/components/transform.hpp"

#include "game/systems/render-system.hpp"

namespace game {

World* loadGameWorld() {
  World* world = new World();

  // clang-format off
  auto background = world->createEntity();
  world->attachComponent(background, Transform{.scale = {600, 600}});
  world->attachComponent(background, Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/background.png")
  });

  auto player = world->createEntity();
  world->attachComponent(player, Transform{.scale = {168, 168}});
  world->attachComponent(player, Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/crosses_0.png")
  });


  world->addSystem(std::make_unique<RenderSystem>());

  // clang-format on

  return world;
}

} // namespace game