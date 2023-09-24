#include <system/application.h>
#include <system/window.h>

#include <system/events/keyboard.h>
#include <system/events/mouse.h>

#include <asset-bundler/bundle.h>
#include <asset-bundler/objects/mesh.h>
#include <asset-bundler/objects/shader.h>

#include <renderer/renderer.h>

#include <asset-bundler/asset_bundler.h>
#include <asset-bundler/loaders/obj_loader.h>
#include <asset-bundler/loaders/shader_loader.h>
#include <asset-bundler/loaders/image_loader.h>

using namespace wind;

class CameraControll {
private:
    float yaw = -90.f,
          pitch = 0.f;
public:
    renderer::Camera* camera;

    float speed = 3.0f;
    float sensitivity = 0.5f;

    CameraControll(renderer::Camera* _camera) {
        camera = _camera;
    }

    void update() {
        // ROTATION
        yaw   += system::Mouse::offset().x * sensitivity;
        pitch += system::Mouse::offset().y * sensitivity;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera->front = glm::normalize(direction);

        // MOVEMENT
        float ds = speed * system::Application::deltaTime();
        if (system::Keyboard::isKey(GLFW_KEY_W))
            camera->position += ds * camera->front;
        if (system::Keyboard::isKey(GLFW_KEY_S))
            camera->position -= ds * camera->front;
        if (system::Keyboard::isKey(GLFW_KEY_A))
            camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * ds;
        if (system::Keyboard::isKey(GLFW_KEY_D))
            camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * ds;
        //
    }
};

int main(int argc, char** argv) {
    assets::Bundler bundler;
    bundler.regLoader(".*(.obj)", new assets::ObjLoader());
    bundler.regLoader(".*(.glsl)", new assets::ShaderLoader());
    bundler.regLoader(".*(.jpg)", new assets::ImageLoader());

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
        self->cursor = false;
    });

    auto asset_mesh = bundle.getResource<assets::Mesh>("./asset/monkey.obj");
    auto asset_shader = bundle.getResource<assets::Shader>("./asset/shader_default.glsl");
    auto asset_image = bundle.getResource<assets::Image>("./asset/stone.jpg");

    auto shader = new renderer::Shader(asset_shader->vtx.c_str(), asset_shader->fgt.c_str());        

    auto texture = new renderer::Texture(asset_image->data, asset_image->width, asset_image->height);

    renderer::Renderer renderer;
    std::shared_ptr<renderer::Mesh> gl_mesh(new renderer::Mesh(
        asset_mesh->vertices, asset_mesh->indices,
        asset_mesh->uv, texture, shader
    ));
    
    delete asset_mesh;
    delete asset_shader;
    delete asset_image;

    auto camera = new renderer::Camera();
    camera->front = {0, 0, -1};
    camera->position = {-5, 0, 0};
    renderer.setCamera(camera);

    auto controll_camera = new CameraControll(camera);

    system::Application::addTerminateCallback([&](){
        delete window;
        delete controll_camera;
        delete camera;
    });

    return system::Application::loop([&](){
        if (system::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            system::Application::quit();

        controll_camera->update();

        renderer.clear();
        renderer.render(
            gl_mesh.get(), 
            {0, 0, 0}, 
            {0, 0, 0}
        );
        window->show();
    });  
}