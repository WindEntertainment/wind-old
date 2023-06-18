#include "Application.h"
#include <SDL2/SDL.h>

namespace app {
    Application* Application::s_app = new Application();

    int Application::loop(int argc, char** argv) {
        return s_app->_loop_(argc, argv);
    }

    int Application::_loop_(int argc, char** argv) {
        //======================================//
        FLAGS_logtostdout = true;
        //FLAGS_log_dir = "./logs/";

        google::InitGoogleLogging(argv[0]);
        //======================================//

        LOG(INFO) << "Libaries initilization...";

        //======================================//

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            LOG(ERROR) << "SDL_Init:" << SDL_GetError();
            return EXIT_FAILURE;
        }

        //======================================//

        LOG(INFO) << "Window creating...";

        m_window = new Window([](Window::CreatingWindowConfig* self) {
            self->title = "Hello SDL2!";
            self->size = {800, 600};
            self->pos = {0, 0};
        });

        m_window->m_window = SDL_CreateWindow(
            "Test",
            0, 0, 800, 600,
            SDL_WINDOW_SHOWN
        );

        //======================================//

        LOG(INFO) << "Start application loop";

        SDL_Surface* window_surface = SDL_GetWindowSurface(m_window->m_window);
        SDL_Surface* image_surface = SDL_LoadBMP("./image.bmp");

        while (isLoopActive()) {
            while (SDL_PollEvent(&m_event)) {
                switch (m_event.type)
                {
                case SDL_QUIT:
                    quit();
                default:
                    break;
                }
            }
            
            SDL_BlitSurface(image_surface, NULL, window_surface, NULL);
            SDL_UpdateWindowSurface(m_window->m_window);
        }

        LOG(INFO) << "Free resources...";

        SDL_FreeSurface(image_surface);
        delete m_window;   
        SDL_Quit();

        return EXIT_SUCCESS;
    }

    inline bool Application::isLoopActive() {
        return m_loop_is_active;
    }

    inline void Application::quit() {
        LOG(INFO) << "Application try quiting...";
        m_loop_is_active = false;
    }
} 