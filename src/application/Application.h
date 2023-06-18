#include "window/Window.h"
namespace app {
    class Application {
    private:
        static Application* s_app;
    public:
        static int loop(int argc, char** argv);

        inline void quit();
        inline bool isLoopActive();
    private:
        int _loop_(int, char**);

        Window* m_window = nullptr;
        bool m_loop_is_active = true;
        SDL_Event m_event = SDL_Event();
    };
}