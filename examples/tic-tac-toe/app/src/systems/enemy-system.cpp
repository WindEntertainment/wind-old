#include <breeze/breeze.hpp>

#include "game/components/game-state.hpp"
#include "game/components/map.hpp"
#include "game/components/renderable.hpp"
#include "game/components/transform.hpp"

#include "game/systems/enemy-system.hpp"

namespace game {

void EnemySystem::update(wind::World& world) {
  auto& state = world.getComponent<GameState>(gameState);

  if (state.stepBy == StepBy::PLAYER)
    return;

  auto& map = world.getComponent<Map>(gameState);

  int x, y;
  do {
    x = rand() % 3;
    y = rand() % 3;
  } while (map.map[x][y] != Sign::EMPTY);

  map.map[x][y] = Sign::TOES;

  world.getComponent<Renderable>(map.cells[x][y]).texture =
    AssetManager::getAsset<Texture>(fmt::format("main/art/toes_{}.png", rand() % 3).c_str());

  state.stepBy = StepBy::PLAYER;
}

} // namespace game
