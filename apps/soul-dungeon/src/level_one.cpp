#include "level_one.h"

#include "transform.h"
#include "mesh.h"

#include "camera_controll.h"
#include "render.h"

#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/image.h>
#include <asset-bundler/objects/shader.h>

namespace soul_dungeon {

    vector<System*> m_systems;

    void LevelOne::build() {
        auto bundle = Game::bundle();
        auto a_mesh = bundle->getResource<assets::Mesh>("./asset/monkey.obj");
        auto a_texture = bundle->getResource<assets::Image>("./asset/stone.jpg");
        auto a_shader = bundle->getResource<assets::Shader>("./asset/shader_default.glsl");

        auto texture = new renderer::Texture(a_texture->data, a_texture->width, a_texture->height);      
        auto shader = new renderer::Shader(a_shader->vtx.c_str(), a_shader->fgt.c_str());
        auto mesh = new renderer::Mesh(
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

        m_systems.push_back(new CameraControll());
        m_systems.push_back(new Render());
    }

    void LevelOne::update() {
        auto registry = Game::registry();

        for (auto system : m_systems)
            system->update(*registry);
    }
}