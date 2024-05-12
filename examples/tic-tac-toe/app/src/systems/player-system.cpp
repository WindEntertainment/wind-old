#include <breeze/breeze.hpp>
#include <input-system/input-system.h>

#include "game/components/game-state.hpp"
#include "game/components/map.hpp"
#include "game/components/renderable.hpp"
#include "game/utils.hpp"

#include "game/systems/player-system.hpp"

namespace game {

PlayerSystem::PlayerSystem() {
  InputSystem::addTriggerCallbacks("player", new std::function([this](InputSystemContext* context) {
    clickPosition = glm::ivec2{
      (int)((context->mouseContext.cursorX - 50) / CELL_SIZE),
      (int)((600 - context->mouseContext.cursorY - 50) / CELL_SIZE)};
  }));
}

PlayerSystem::~PlayerSystem() {
  // ToDo: remove callbacks
}

void PlayerSystem::update(wind::World& world) {
  auto& state = world.getComponent<GameState>(gameState);

  if (state.stepBy == StepBy::ENEMY)
    return;

  if (
    clickPosition.x < 0 || clickPosition.y < 0 ||
    clickPosition.x >= MAP_WIDTH || clickPosition.y >= MAP_HEIGHT)
    return;

  auto& map = world.getComponent<Map>(gameState);

  if (map.map[clickPosition.x][clickPosition.y] != Sign::EMPTY)
    return;

  map.map[clickPosition.x][clickPosition.y] = Sign::CROSSES;

  // clang-format off
  world.attachComponent( map.cells[clickPosition.x][clickPosition.y], Renderable {
    .texture = AssetManager::getAsset<Texture>(fmt::format("main/art/crosses_{}.png", rand() % 3).c_str())
  });
  // clang-format on

  state.stepBy = StepBy::ENEMY;
}

} // namespace game