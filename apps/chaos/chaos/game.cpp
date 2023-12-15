#include "game.h"

namespace chaos {
    int Game::main() {
        return breeze::Game().main([&](breeze::GameParameters* self){
            self->bundle = "./assets.bundle";
            self->window = [](system::Window::WindowConfig* self) {
                self->close_event = system::Application::quit;
                self->fullscreen = false;
                self->size = {1280, 860};
                self->cursor = false;
            };
        });
    }
}