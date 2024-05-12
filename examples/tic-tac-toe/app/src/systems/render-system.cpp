#include <breeze/breeze.hpp>
#include <renderer/renderer.hpp>

#include "game/components/renderable.hpp"
#include "game/components/transform.hpp"
#include "game/systems/render-system.hpp"

namespace game {

void RenderSystem::update(wind::World& world) {
  wind::Renderer::clear({1.f, 1.f, 1.f, 1});

  world.forEachWith<Renderable, Transform>([](const Renderable& renderable, const Transform& transform) {
    wind::Renderer::drawTexture(renderable.texture, {1, 1}, transform.position, {0, 0, 0}, transform.scale);
  });
}

} // namespace game