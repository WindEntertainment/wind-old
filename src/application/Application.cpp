#include "Application.h"
#include <SDL2/SDL.h>

namespace app {
    Application* Application::s_app = new Application();

    int Application::loop() {
        return s_app->_loop_();
    }

    int Application::_loop_() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            return EXIT_FAILURE;

        m_window = new Window([](Window::CreatingWindowConfig* self) {
            self->title = "Hello SDL2!";
            self->size = {800, 600};
            self->pos = {0, 0};
        });

        return EXIT_SUCCESS;
    }
} 