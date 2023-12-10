#include "render.h"
#include "../game.h"

#include <std-game/transform.h>
#include <std-game/renderable.h>

#include <renderer/renderer.h>

namespace soul_dungeon {
    void Render::update(entt::registry& registry) {            
        registry.view<renderer::Camera>().each([&](auto entity, auto& camera) {
            registry.view<stdgame::Transform, stdgame::Renderable>().each([&](
                auto entity, auto& transform, auto& renderable
            ) {
                Game::renderer()->render(
                    &camera, 
                    renderable.mesh, renderable.texture, renderable.tiling, renderable.shader,
                    transform.position, transform.rotation, transform.scale
                );
            });
        });
    }
}