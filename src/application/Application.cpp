#include "Application.h"

namespace app {
    void glfwErrorCallback(int _code, const char* _description) {
        logger()->error() << "glfw(" << _code << "):" << _description;
    } 

    Application* Application::s_app = new Application();

    Application* Application::instance() {
        return s_app;
    }

    int Application::loop(int argc, char** argv) {
        return s_app->_loop_(argc, argv);
    }

    int Application::_loop_(int argc, char** argv) {

        atexit(quitCallback);
        
        //======================================//
        logger()->info() << "Libaries initilization...";

        //======================================//

        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit()) {
            logger()->error() << "Fail glfwInit:";
            return EXIT_FAILURE;
        }

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        logger()->info() << "glfw version:" << major << "." << minor << "." << revision;

        //======================================//

        logger()->info() << "Window creating...";

        m_window = new Window([](Window::CreatingWindowConfig* self) {
            self->title = "SoulDungeon";
            self->size = {800, 600};
            self->pos = {0, 0};
        });

        //======================================//

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            logger()->error() << "Failed GLAD load gl loader";
            return EXIT_FAILURE;
        }

        glViewport(0, 0, m_window->size().x, m_window->size().y);

        //======================================//

        auto shader = app::Resources::load<app::Shader>("./asset/shader");
        auto mesh = app::Resources::load<app::Mesh>("./asset/monkey.obj");
        
        m_world = new World();
        m_renderer = new Renderer(m_world);

        auto entity = new Entity();

        auto transform = new Transform({0, 0, -5}, {0, 0, 0});
        entity->addComponent(transform);
        entity->addComponent(new Model(mesh, shader));

        m_world->addEntity(entity);

        //======================================//

        logger()->info() << "Start application loop";

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

        return EXIT_SUCCESS;
    }

    bool Application::isLoopActive()  {
        return m_loop_is_active;
    }

    void Application::quit() {
        logger()->info() << "Application try quiting...";
        m_loop_is_active = false;
    }

    void Application::quitCallback() {
        logger()->info() << "Free resources...";

        delete s_app->m_window;
        delete s_app->m_world;
        delete s_app->m_renderer;

        glfwTerminate();
    }
} 