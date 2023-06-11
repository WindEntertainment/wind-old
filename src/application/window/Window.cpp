#include "Window.h"

namespace app {
    Window::Window(void (*buildConfig)(CreatingWindowConfig*)) {
        CreatingWindowConfig config;
        buildConfig(&config);

        window = SDL_CreateWindow(
            config.title.c_str(),
            config.pos.x, config.pos.y,
            config.size.x, config.size.y,
            SDL_WINDOW_SHOWN
        );

        SDL_UpdateWindowSurface(window);
        SDL_Delay(1000);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}