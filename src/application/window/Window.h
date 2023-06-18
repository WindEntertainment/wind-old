#include "../../utlis.h"
#include <SDL2/SDL.h>

namespace app {
    class Window {
    public:
        struct CreatingWindowConfig;
        SDL_Window* m_window;
    private:
    public:
        Window(void (*)(CreatingWindowConfig* self));
        ~Window();
    };

    struct Window::CreatingWindowConfig {
        string title;
        vec2 size;
        vec2 pos;
    };
}