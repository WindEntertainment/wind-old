#include "game.h"

#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/shader.h>

#include <system/events/keyboard.h>

namespace soul_dungeon {
    Game* Game::singlton = nullptr;

    assets::Bundle* Game::bundle() {
        return singlton->m_bundle;
    } 

    renderer::Renderer* Game::renderer() {
        return singlton->m_renderer;
    }

    system::Window* Game::window() {
        return singlton->m_window;
    }

    entt::registry* Game::registry() {
        return singlton->m_registry;
    }

    int Game::play(Level* _level) {
        if (singlton)
            return -1;
        singlton = this;

        system::Application::init([](){
            return true;
        }); 

        m_bundle = new assets::Bundle("./assets.bundle");
        if (!m_bundle->isOpen())
            return system::Application::terminate();

        m_window = new system::Window([](system::Window::WindowConfig* self) {
            self->close_event = system::Application::quit;
            self->fullscreen = false;
            self->size = {1280, 860};
            self->cursor = false;
        });

        m_renderer = new renderer::Renderer();

        m_registry = new entt::registry();

        system::Application::addTerminateCallback([&](){
            delete _level;
            
            m_registry->clear();
            delete m_registry;

            delete m_renderer;
            delete m_window;
            delete m_bundle;
        });

        _level->build();
        return system::Application::loop([&](){
            if (system::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
                system::Application::quit();

            m_renderer->clear();
            _level->update();
            m_window->show();
        });  
    }
}