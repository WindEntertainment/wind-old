#include "application.h"

#include <asset-bundler/asset_bundler.h>
#include <asset-bundler/bundle.h>

#include <asset-bundler/objects/shader.h>

namespace wind {
    void glfwErrorCallback(int _code, const char* _description) {
        log().error() << "glfw(" << _code << "):" << _description;
    } 

    Application* Application::s_app = new Application();

    Application* Application::instance() {
        return s_app;
    }

    int Application::loop(int argc, char** argv) {
        return s_app->_loop_(argc, argv);
    }

    int Application::_loop_(int argc, char** argv) {
        //======================================//
        log().info() << "Libaries initilization...";

        //======================================//

        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit()) {
            log().error() << "Fail glfwInit:";
            return EXIT_FAILURE;
        }

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        log().info() << "glfw version:" << major << "." << minor << "." << revision;

        //======================================//

        log().info() << "Window creating...";

        m_window = new Window([](Window::CreatingWindowConfig* self) {
            self->title = "SoulDungeon";
            self->size = {800, 600};
            self->pos = {0, 0};
        });

        //======================================//

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            log().error() << "Failed GLAD load gl loader";
            return EXIT_FAILURE;
        }

        glViewport(0, 0, m_window->size().x, m_window->size().y);

        //======================================//

        auto bundle = wind::assets::Bundle();
        bundle.load("assets.bundle");

        auto asset_shader = bundle.getResource<wind::assets::Shader>("./asset/shader_default.glsl");
        auto asset_mesh   = bundle.getResource<wind::assets::Mesh>("./asset/monkey.obj");
        
        auto shader =  new Shader(asset_shader->vtx.c_str(), asset_shader->fgt.c_str());

        m_world = new World();
        m_renderer = new Renderer(m_world);

        auto entity = new Entity();

        auto transform = new Transform({0, 0, -5}, {0, 0, 0});
        entity->addComponent(transform);
        entity->addComponent(new Mesh(asset_mesh, shader));

        m_world->addEntity(entity);

        //======================================//

        log().info() << "Start application loop";

        while (isLoopActive()) {
            if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
                quit();
            
            transform->rotation.x += 0.1;
            transform->rotation.y += 0.1;
            transform->rotation.z += 0.1;

            m_renderer->render();
            m_window->show();
            
            glfwPollEvents(); 
        }

        quitCallback();
        return EXIT_SUCCESS;
    }

    bool Application::isLoopActive()  {
        return m_loop_is_active;
    }

    void Application::quit() {
        log().info() << "Application try quiting...";
        m_loop_is_active = false;
    }

    void Application::quitCallback() {
        log().info() << "Free resources...";

        delete s_app->m_window;
        delete s_app->m_world;
        delete s_app->m_renderer;

        glfwTerminate();
    }
} 