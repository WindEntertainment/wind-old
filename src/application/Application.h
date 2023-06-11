#include "window/Window.h"
namespace app {
    class Application {
    private:
        static Application* s_app;
    public:
        static int loop();
    private:
        int _loop_();
        Window* m_window = nullptr;
    };
}