#include "level_one.h"

#include <breeze/components/transform.h>
#include <breeze/components/renderable.h>

#include "systems/camera_controll.h"
#include <breeze/systems/render.h>

#include <resources/resource_manager.h>

#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/image.h>
#include <asset-bundler/objects/shader.h>
#include <asset-bundler/objects/text.h>

#include <breeze/prefab/prefab.h>

namespace soul_dungeon {

    vector<breeze::System*> m_systems;

    void LevelOne::build() {
        auto bundle = Game::bundle();
        resources::addBundle(bundle);

        auto prefab = resources::get<breeze::Prefab>("./asset/scenes/scene.prefab");

        auto registry = Game::registry();

        auto scene = prefab->instance(*registry);

        auto e_camera = registry->create();
        auto camera = registry->emplace<renderer::Camera>(e_camera, renderer::Camera{
            vec3{0, -4, 5}, 
            vec3{0, 0, -1},
            vec3{0, 1, 0}
        });

        m_systems.push_back(new CameraControll());
        m_systems.push_back(new breeze::Render(Game::renderer()));
    }

    void LevelOne::update() {
        auto registry = Game::registry();

        for (auto system : m_systems)
            system->update(*registry);
    }
}