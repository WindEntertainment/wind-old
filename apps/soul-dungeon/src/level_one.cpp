#include "level_one.h"

#include <std-game/transform.h>
#include <std-game/renderable.h>

#include "systems/camera_controll.h"
#include "systems/render.h"

#include <resources/resource_manager.h>

#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/image.h>
#include <asset-bundler/objects/shader.h>
#include <asset-bundler/objects/text.h>

namespace soul_dungeon {

    vector<stdgame::System*> m_systems;

    void LevelOne::build() {
        auto bundle = Game::bundle();
        resources::addBundle(bundle);

        auto texture = resources::get<renderer::Texture>("./asset/stone.jpg");      
        auto shader = resources::get<renderer::Shader>("./asset/shader_default.glsl");
        auto mesh = resources::get<renderer::Mesh>("./asset/monkey.obj");

        mesh->m_texture = texture;
        mesh->m_shader = shader;

        auto registry = Game::registry();

        auto monkey = registry->create();
        registry->emplace<stdgame::Renderable>(monkey, mesh);
        registry->emplace<stdgame::Transform>(monkey, stdgame::Transform{
            vec3{0, 0, 0},
            vec3{0, 0, 0},
            vec3(5, 5, 5)
        });
        
        auto monkey2 = registry->create();
        registry->emplace<stdgame::Renderable>(monkey2, mesh);
        registry->emplace<stdgame::Transform>(monkey2, stdgame::Transform{
            vec3{-15, 0, 0},
            vec3{0, 0, 0},
            vec3(5, 5, 5)
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