#include "breeze.h"

#include <asset-bundler/bundle.h>

namespace wind {
    namespace breeze {
        int Game::main(std::function<void(GameParameters* self)> _args) {
            // 
            auto args = new GameParameters();
            _args(args);

            // library init
            system::Application::init([](){
                return true;
            }); 

            // load resource bundle 
            auto bundle = new assets::Bundle(std::move(args->bundle));
            if (!bundle->isOpen())
                return system::Application::terminate();

            // create window
            auto window = new system::Window(args->window);

            auto renderer = new renderer::Renderer();
            auto registry = new entt::registry();

            breeze::ComponentRegistry::init();

            return system::Application::loop([&](){
                if (system::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
                    system::Application::quit();

                renderer->clear();
                window->show();
            });  
        }
    }
}