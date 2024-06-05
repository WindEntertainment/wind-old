#include "breeze/breeze.hpp"

#include "game/components/enemy.hpp"
#include "game/components/moveable.hpp"
#include "game/components/transform.hpp"
#include "game/systems/following-system.hpp"
#include <glm/ext/scalar_constants.hpp>

namespace game {

void FollowingSystem::update(wind::World& world) {
  world.forEachWith<Moveable, Transform, Enemy>([&world](Moveable& moveable, const Transform& transform, const Enemy& enemy) {
    glm::vec2 velocity = glm::normalize(world.getComponent<Transform>(enemy.target).position - transform.position + glm::epsilon<float>());
    moveable.velocity = glm::vec3{velocity.x, velocity.y, 0} / 2.f;
  });
}

} // namespace game