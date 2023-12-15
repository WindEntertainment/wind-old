#include "render.h"

#include <breeze/components/transform.h>
#include <breeze/components/renderable.h>

#include <renderer/renderer.h>

namespace wind {
    namespace breeze {
        Render::Render(wind::renderer::Renderer* _renderer) {
            m_renderer = _renderer;
        }

        void Render::update(entt::registry& registry) {            
            registry.view<renderer::Camera>().each([&](auto entity, auto& camera) {
                registry.view<breeze::Transform, breeze::Renderable>().each([&](
                    auto entity, auto& transform, auto& renderable
                ) {
                    m_renderer->render(
                        &camera, 
                        renderable.mesh, renderable.texture, renderable.tiling, renderable.shader,
                        transform.position, transform.rotation, transform.scale
                    );
                });
            });
        }
    }
}