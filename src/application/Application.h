#include "renderer/Renderer.h"
namespace app {
    class Application {
    private:
        static Application* s_app;
    public:
        static Application* instance();
        static int loop(int argc, char** argv);

        void quit();
        bool isLoopActive();
    private:
        int _loop_(int, char**);

        static void quitCallback();

        Window* m_window = nullptr;
        Renderer* m_renderer = nullptr;
        bool m_loop_is_active = true;
    };
}