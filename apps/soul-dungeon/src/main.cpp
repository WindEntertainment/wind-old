#include <renderer/renderer.h>

#include <system/application.h>
#include <system/window.h>
#include <system/events/keyboard.h>

int main(int argc, char** argv) {
    using namespace wind::system;

    Application::init();
    
    Window win([](Window::WindowConfig* self) {
        self->close_event = Application::quit;
        self->fullscreen = false;
    });

    return Application::loop([&](){
        if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            Application::quit();
        win.show();
    });  
}