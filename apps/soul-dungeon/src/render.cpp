#include "render.h"
#include "game.h"

#include <std-game/transform.h>
#include <std-game/mesh.h>

#include <renderer/renderer.h>

namespace soul_dungeon {
    void Render::update(entt::registry& registry) {            
        registry.view<renderer::Camera>().each([&](auto entity, auto& camera) {
            registry.view<stdgame::Transform, stdgame::Mesh>().each([&](auto entity, auto& transform, auto& mesh) {
                Game::renderer()->render(&camera, mesh.mesh, transform.position, transform.rotation, transform.scale);
            });
        });
    }
}