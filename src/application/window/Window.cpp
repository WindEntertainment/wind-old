#include "Window.h"

namespace app {
    Window::Window(void (*buildConfig)(CreatingWindowConfig*)) {
        CreatingWindowConfig config;
        buildConfig(&config);

      /*  m_window = SDL_CreateWindow(
            config.title.c_str(),
            config.pos.x, config.pos.y,
            config.size.x, config.size.y,
            SDL_WINDOW_SHOWN
        );

        if (!m_window) {
            LOG(ERROR) << "SDL_CreateWindow returned null:" << SDL_GetError();
            return;
        }*/
    }

    Window::~Window() {
        if (!m_window)
            return;
        SDL_DestroyWindow(m_window);
    }
}