#include "level_one.h"

#include "transform.h"
#include "mesh.h"

#include "camera_controll.h"

#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/image.h>
#include <asset-bundler/objects/shader.h>

namespace soul_dungeon {

    CameraControll* camera_controll = nullptr;
    renderer::Mesh* mesh = nullptr;

    void LevelOne::build() {
        auto bundle = Game::bundle();
        auto a_mesh = bundle->getResource<assets::Mesh>("./asset/monkey.obj");
        auto a_texture = bundle->getResource<assets::Image>("./asset/stone.jpg");
        auto a_shader = bundle->getResource<assets::Shader>("./asset/shader_default.glsl");

        auto texture = new renderer::Texture(a_texture->data, a_texture->width, a_texture->height);      
        auto shader = new renderer::Shader(a_shader->vtx.c_str(), a_shader->fgt.c_str());
        mesh = new renderer::Mesh(
            a_mesh->vertices, a_mesh->indices, a_mesh->uv,
            texture, shader
        );

        auto registry = Game::registry();

        auto monkey = registry->create();
        registry->emplace<Mesh>(monkey, mesh);
        registry->emplace<Transform>(monkey, Transform{
            vec3{0, 0, 0},
            vec3{0, 0, 0}
        });
        
        auto e_camera = registry->create();
        auto camera = registry->emplace<renderer::Camera>(e_camera, renderer::Camera{
            vec3{0, 0, 5},
            vec3{0, 0, -1},
            vec3{0, 1, 0}
        });

        camera_controll = new CameraControll();
    }

    void LevelOne::update() {
        auto registry = Game::registry();

        camera_controll->update();
        registry->view<renderer::Camera>().each([&](auto entity, auto& camera) {
            registry->view<Transform, Mesh>().each([&](auto entity, auto& transform, auto& mesh) {
                Game::renderer()->render(&camera, mesh.mesh, transform.position, transform.rotation);
            });
        });
    }
}