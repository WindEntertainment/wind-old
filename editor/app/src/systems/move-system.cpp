#include "breeze/breeze.hpp"

#include "game/components/moveable.hpp"
#include "game/components/transform.hpp"
#include "game/systems/move-system.hpp"

namespace game {

void MoveSystem::update(wind::World& world) {
  world.forEachWith<Moveable, Transform>([](const Moveable& moveable, Transform& transform) {
    transform.position += moveable.velocity;
  });
}

} // namespace game