#include "Application.h"

namespace app {
    void glfwErrorCallback(int _code, const char* _description) {
        LOG(ERROR) << "glfw(" << _code << "):" << _description;
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
        FLAGS_logtostdout = true;
        //FLAGS_log_dir = "./logs/";

        google::InitGoogleLogging(argv[0]);

        LOG(INFO) << "Libaries initilization...";

        //======================================//

        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit()) {
            LOG(ERROR) << "Fail glfwInit:";
            return EXIT_FAILURE;
        }

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        LOG(INFO) << "glfw version:" << major << "." << minor << "." << revision;
  
        //======================================//

        LOG(INFO) << "Window creating...";

        m_window = new Window([](Window::CreatingWindowConfig* self) {
            self->title = "Hello GLFW3!";
            self->size = {800, 600};
            self->pos = {0, 0};
        });

        //======================================//

        LOG(INFO) << "Start application loop";

        while (isLoopActive()) {
            if (Keyboard::isKey(GLFW_KEY_ESCAPE))
                quit();
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(m_window->m_window);
            glfwPollEvents();
        }

        return EXIT_SUCCESS;
    }

    bool Application::isLoopActive() {
        return m_loop_is_active;
    }

    void Application::quit() {
        LOG(INFO) << "Application try quiting...";
        m_loop_is_active = false;
    }

    void Application::quitCallback() {
        LOG(INFO) << "Free resources...";
        glfwTerminate();
    }
} 