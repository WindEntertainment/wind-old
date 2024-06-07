#include "breeze/breeze.hpp"
#include "game/utils.hpp"
#include "game/worlds.hpp"

#include "game/components/game-state.hpp"
#include "game/components/map.hpp"
#include "game/components/renderable.hpp"
#include "game/components/transform.hpp"

#include "game/systems/enemy-system.hpp"
#include "game/systems/player-system.hpp"
#include "game/systems/render-system.hpp"
#include "game/systems/tictactoe-system.hpp"

namespace game {

World* loadGameWorld() {
  World* world = new World();

  auto gameState = world->createEntity();

  auto background = world->createEntity();
  world->attachComponent(background, Transform{.scale = {600, 600}});
  world->attachComponent(background, Renderable{.texture = AssetManager::getAsset<Texture>("main/art/background.png")});

  Map map;
  for (int i = 0; i < MAP_WIDTH; ++i)
    for (int j = 0; j < MAP_HEIGHT; ++j) {
      map.cells[i][j] = world->createEntity();
      world->attachComponent(map.cells[i][j], Renderable{.texture = nullptr});
      world->attachComponent(map.cells[i][j], Transform{.position = {-168 + i * 168, -178 + j * 168, 0}, .scale = {168, 168}});
    }

  world->attachComponent(gameState, map);
  world->attachComponent(gameState, GameState{.stepBy = StepBy::PLAYER});

  world->addSystem(std::make_unique<RenderSystem>());
  world->addSystem(std::make_unique<TicTacToeSystem>());
  world->addSystem(std::make_unique<EnemySystem>());
  world->addSystem(std::make_unique<PlayerSystem>());

  return world;
}

} // namespace game
