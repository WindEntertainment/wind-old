#include "../../utlis.h"
#include <SDL2/SDL.h>

namespace app {
    class Window {
    public:
        struct CreatingWindowConfig;
    private:
        SDL_Window* window;
    public:
        Window(void (*)(CreatingWindowConfig* self));
    };

    struct Window::CreatingWindowConfig {
        string title;
        vec2 size;
        vec2 pos;
    };
}