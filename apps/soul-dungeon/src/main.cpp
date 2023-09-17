
#include <system/application.h>
#include <system/window.h>
#include <system/events/keyboard.h>

#include <asset-bundler/bundle.h>
#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/shader.h>

#include <renderer/renderer.h>

int main(int argc, char** argv) {
    using namespace wind;

    system::Application::init();
    
    assets::Bundle bundle;
    bundle.load("./assets.bundle");

    system::Window window([](system::Window::WindowConfig* self) {
        self->close_event = system::Application::quit;
        self->fullscreen = false;
    });

    auto asset_mesh = bundle.getResource<assets::Mesh>("./asset/monkey.obj");
    auto asset_shader = bundle.getResource<assets::Shader>("./asset/shader_default.glsl");

    auto shader = new renderer::Shader(asset_shader->vtx.c_str(), asset_shader->fgt.c_str());        

    renderer::Renderer renderer;
    std::shared_ptr<renderer::Mesh> gl_mesh(new renderer::Mesh(
        asset_mesh->vertices, asset_mesh->indices, shader
    ));

    return system::Application::loop([&](){
        if (system::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            system::Application::quit();

        renderer.clear();
        renderer.render(
            gl_mesh.get(), 
            {0, 0, -5}, {0, 30, 30}
        );
        window.show();
    });  
}