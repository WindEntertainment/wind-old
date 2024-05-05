#include "breeze/breeze.hpp"

#include "game/components/renderable.hpp"
#include "game/components/transform.hpp"
#include "game/systems/render-system.hpp"

namespace game {
void RenderSystem::update(wind::World& world) {
  Renderer::clear({0.f, 0.f, 0.f, 1});

  world.forEachWith<Renderable, Transform>([](const Renderable& renderable, const Transform& transform) {
    Renderer::drawTexture(renderable.texture, {1, 1}, transform.position, {0, 0, 0}, transform.scale);
  });
}
} // namespace game