#include <renderer/renderer.h>

#include <system/application.h>
#include <system/window.h>

int main(int argc, char** argv) {
    using namespace wind::system;

    Application::init();
    
    Window win([](Window::WindowConfig* self) {
        self->fullscreen = false;
    });

    return Application::loop([&](){
        win.show();
    });  
}