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

#include <std-game/prefab.h>

namespace soul_dungeon {

    vector<stdgame::System*> m_systems;

    void LevelOne::build() {
        auto bundle = Game::bundle();
        resources::addBundle(bundle);

        auto texture = resources::get<renderer::Texture>("./asset/stone.jpg");      
        auto shader = resources::get<renderer::Shader>("./asset/shader_default.glsl");
        auto mesh = resources::get<renderer::Mesh>("./asset/monkey.obj");
        auto prefab = resources::get<stdgame::Prefab>("./asset/monkey.prefab");

        mesh->m_texture = texture;
        mesh->m_shader = shader;

        auto registry = Game::registry();

        auto monkey = prefab->instance(*registry);
      //  registry->get<stdgame::Transform>(monkey).position = {-15, 0, 0};

        auto monkey2 = prefab->instance(*registry);

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