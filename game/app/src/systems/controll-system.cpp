#include <breeze/breeze.hpp>
#include <input-system/input-system.h>

#include "game/components/moveable.hpp"
#include "game/components/player.hpp"
#include "game/components/transform.hpp"
#include "game/systems/controll-system.hpp"

namespace game {

using namespace wind;

ControllSystem::ControllSystem() {
  InputSystem::addTriggerCallbacks("playerMoveUpPressed", new std::function([this](InputSystemContext* context) {
    velocity.y = 1;
  }));
  InputSystem::addTriggerCallbacks("playerMoveDownPressed", new std::function([this](InputSystemContext* context) {
    velocity.y = -1;
  }));
  InputSystem::addTriggerCallbacks("playerMoveLeftPressed", new std::function([this](InputSystemContext* context) {
    velocity.x = -1;
  }));
  InputSystem::addTriggerCallbacks("playerMoveRightPressed", new std::function([this](InputSystemContext* context) {
    velocity.x = 1;
  }));

  InputSystem::addTriggerCallbacks("playerMoveUpReleased", new std::function([this](InputSystemContext* context) {
    velocity.y = velocity.y == 1 ? 0 : velocity.y;
  }));
  InputSystem::addTriggerCallbacks("playerMoveDownReleased", new std::function([this](InputSystemContext* context) {
    velocity.y = velocity.y == -1 ? 0 : velocity.y;
  }));
  InputSystem::addTriggerCallbacks("playerMoveLeftReleased", new std::function([this](InputSystemContext* context) {
    velocity.x = velocity.x == -1 ? 0 : velocity.x;
  }));
  InputSystem::addTriggerCallbacks("playerMoveRightReleased", new std::function([this](InputSystemContext* context) {
    velocity.x = velocity.x == 1 ? 0 : velocity.x;
  }));
}

ControllSystem::~ControllSystem() {
  // InputSystem::removeTriggerCallback
}

void ControllSystem::update(wind::World& world) {
  world.forEachWith<Player, Moveable>([&](const Player& _, Moveable& moveable) {
    moveable.velocity = velocity;
  });
}

} // namespace game