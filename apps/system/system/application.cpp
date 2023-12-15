#include "application.h"

namespace wind {
    namespace system {
        bool Application::is_alive = false;
        float Application::delta_time = 0.f;

        vector<std::function<void()>> Application::OnTerminateEvent;
        std::function<bool()> Application::OnQuitEvent;        

        float Application::deltaTime() {
            return delta_time;
        }

        bool Application::alive() {
            return is_alive;
        }

        void Application::quit() {
            if (!OnQuitEvent) {
                is_alive = false;
                return;
            }

            is_alive = !OnQuitEvent();
        }

        void Application::init(std::function<bool()> try_quiting) {
            log().info() << "Application initilization...";

            OnQuitEvent = try_quiting;

            //============================================================//

            if (!glfwInit()) {
                log().error() << "Fail glfwInit:" << getGLFWError();
                return;
            }

            int major, minor, revision;
            glfwGetVersion(&major, &minor, &revision);
            log().info() << "glfw version:" << major << "." << minor << "." << revision;
        
            //============================================================//

            is_alive = true;
        }

        int Application::terminate() {
            for (auto callback : OnTerminateEvent) 
                callback();
            // glfwTerminate() // segmentation fault
            return EXIT_FAILURE;
        }

        void Application::addTerminateCallback(std::function<void()> callback) {
            assert(callback != nullptr);
            OnTerminateEvent.push_back(callback);   
        }

        int Application::loop(std::function<void()> update) {
            log().info() << "Start application loop";

            glEnable(GL_DEPTH_TEST);

            float lastTime = glfwGetTime();
            while (alive()) {
                delta_time = glfwGetTime() - lastTime;
                lastTime = glfwGetTime();

                if (update)
                    update();
                    
                glfwPollEvents();
            };

            terminate();
            return EXIT_SUCCESS;
        }
    }
}