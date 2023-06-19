#include "Application.h"
#include <SDL2/SDL.h>

namespace app {
    void glfwErrorCallback(int _code, const char* _description) {
        LOG(ERROR) << "glfw(" << _code << "):" << _description;
    } 

    void quitCallback() {
        LOG(INFO) << "Free resources...";
        glfwTerminate();
    }

    Application* Application::s_app = new Application();

    int Application::loop(int argc, char** argv) {
        return s_app->_loop_(argc, argv);
    }

    int Application::_loop_(int argc, char** argv) {
        //======================================//
        FLAGS_logtostdout = true;
        //FLAGS_log_dir = "./logs/";

        google::InitGoogleLogging(argv[0]);

        LOG(INFO) << "Libaries initilization...";

        //======================================//

        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit()) {
            LOG(ERROR) << "fail glfwInit";
            return EXIT_FAILURE;
        }

        //======================================//

        LOG(INFO) << "Window creating...";

        m_window = new Window([](Window::CreatingWindowConfig* self) {
            self->title = "Hello GLFW3!";
            self->size = {800, 600};
            self->pos = {0, 0};
        });

        //======================================//

        LOG(INFO) << "Start application loop";

        while (isLoopActive() && !glfwWindowShouldClose(m_window->m_window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(m_window->m_window);
            glfwPollEvents();
        }

        atexit(quitCallback);
        return EXIT_SUCCESS;
    }

    inline bool Application::isLoopActive() {
        return m_loop_is_active;
    }

    inline void Application::quit() {
        LOG(INFO) << "Application try quiting...";
        m_loop_is_active = false;
    }
} 