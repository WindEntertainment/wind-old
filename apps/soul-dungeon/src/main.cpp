#include <system/application.h>
#include <system/window.h>
#include <system/events/keyboard.h>

#include <asset-bundler/bundle.h>
#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/shader.h>

#include <renderer/renderer.h>

#include <asset-bundler/asset_bundler.h>
#include <asset-bundler/loaders/obj_loader.h>
#include <asset-bundler/loaders/shader_loader.h>
#include <asset-bundler/loaders/image_loader.h>

int main(int argc, char** argv) {
    using namespace wind;

    assets::Bundler bundler;
    bundler.regLoader(".*(.obj)", new assets::ObjLoader());
    bundler.regLoader(".*(.glsl)", new assets::ShaderLoader());
    bundler.regLoader(".*(.png)", new assets::ImageLoader());

    bundler.assembly("./asset/", "./assets.bundle");

    system::Application::init([](){
        return true;
    });
    
    assets::Bundle bundle("./assets.bundle");
    if (!bundle.isOpen())
        return system::Application::terminate();

    auto window = new system::Window([](system::Window::WindowConfig* self) {
        self->close_event = system::Application::quit;
        self->fullscreen = false;
    });

    auto asset_mesh = bundle.getResource<assets::Mesh>("./asset/monkey.obj");
    auto asset_shader = bundle.getResource<assets::Shader>("./asset/shader_default.glsl");
    auto asset_image = bundle.getResource<assets::Image>("./asset/dice.png");

    auto shader = new renderer::Shader(asset_shader->vtx.c_str(), asset_shader->fgt.c_str());        

    auto texture = new renderer::Texture(asset_image->data, asset_image->width, asset_image->height);

    renderer::Renderer renderer;
    std::shared_ptr<renderer::Mesh> gl_mesh(new renderer::Mesh(
        asset_mesh->vertices, asset_mesh->indices,
        asset_mesh->uv, shader
    ));

    delete asset_mesh;
    delete asset_shader;
    delete asset_image;

    system::Application::addTerminateCallback([&](){
        delete window;
    });

    return system::Application::loop([&](){
        if (system::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            system::Application::quit();

        renderer.clear();
        renderer.render(
            gl_mesh.get(), 
            {0, 0, -5}, {0, 30, 30}
        );
        window->show();
    });  
}