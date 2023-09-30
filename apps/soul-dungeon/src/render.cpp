#include "render.h"

#include "transform.h"
#include "mesh.h"

#include <renderer/renderer.h>

namespace soul_dungeon {
    void Render::update(entt::registry& registry) {            
        registry.view<renderer::Camera>().each([&](auto entity, auto& camera) {
            registry.view<Transform, Mesh>().each([&](auto entity, auto& transform, auto& mesh) {
                Game::renderer()->render(&camera, mesh.mesh, transform.position, transform.rotation, transform.scale);
            });
        });
    }
}