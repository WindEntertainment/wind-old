#include <breeze/breeze.hpp>
#include <input-system/input-system.h>

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
  if (
    clickPosition == glm::ivec2(-1, -1) ||
    clickPosition.x < 0 || clickPosition.y < 0 ||
    clickPosition.x >= MAP_WIDTH || clickPosition.y >= MAP_HEIGHT)
    return;

  auto map = world.getComponent<Map>(gameState);
  map.map[clickPosition.x][clickPosition.y] = Sign::CROSSES;

  // clang-format off
  world.attachComponent( map.cells[clickPosition.x][clickPosition.y],Renderable{
    .texture = AssetManager::getAsset<Texture>("main/art/crosses_0.png")
  });
  // clang-format on

  clickPosition = glm::ivec2(-1, -1);
}

} // namespace game