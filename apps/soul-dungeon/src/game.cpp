#include "game.h"

#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/shader.h>

#include <system/window.h>

#include <system/events/keyboard.h>

namespace soul_dungeon {
    bool tryQuit() {
        return true;
    }

    int Game::play() {
        if (singlton)
            return -1;
        singlton = this;

        system::Application::init(tryQuit); 

        m_bundle.load("./assets.bundle");
        if (!m_bundle.isOpen())
            return system::Application::terminate();

        auto window = new system::Window([](system::Window::WindowConfig* self) {
            self->close_event = system::Application::quit;
            self->fullscreen = false;
            self->size = {1280, 720};
            self->cursor = false;
        });

        system::Application::addTerminateCallback([&](){
            delete window;
        });

        return system::Application::loop([&](){
            if (system::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
                system::Application::quit();

            window->show();
        });  
    }
}