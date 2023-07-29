#include "Application.h"

namespace app {
    void glfwErrorCallback(int _code, const char* _description) {
        // LOG(ERROR) << "glfw(" << _code << "):" << _description;
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
        //FLAGS_logtostdout = true;
        //FLAGS_log_dir = "./logs/";

        //google::InitGoogleLogging(argv[0]);

        // LOG(INFO) << "Libaries initilization...";

        //======================================//

        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit()) {
            // LOG(ERROR) << "Fail glfwInit:";
            return EXIT_FAILURE;
        }

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        // LOG(INFO) << "glfw version:" << major << "." << minor << "." << revision;

        //======================================//

        // LOG(INFO) << "Window creating...";

        m_window = new Window([](Window::CreatingWindowConfig* self) {
            self->title = "SoulDungeon";
            self->size = {800, 600};
            self->pos = {0, 0};
        });

        //======================================//

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            // LOG(ERROR) << "Failed GLAD load gl loader";
            return EXIT_FAILURE;
        }

        //======================================//

        auto shader = app::Resources::load<app::Shader>("./asset/shader");
        auto mesh = app::Resources::load<app::Mesh>("./asset/cube.obj");
        
        m_world = new World();
        m_world->mesh = mesh;
        m_world->shader = shader;

        m_renderer = new Renderer(m_world);

        //======================================//

        // LOG(INFO) << "Start application loop";

        while (isLoopActive()) {
            if (Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
                quit();
            
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
        // LOG(INFO) << "Application try quiting...";
        m_loop_is_active = false;
    }

    void Application::quitCallback() {
        // LOG(INFO) << "Free resources...";

        delete s_app->m_window;
        delete s_app->m_world;
        delete s_app->m_renderer;

        glfwTerminate();
    }
} 