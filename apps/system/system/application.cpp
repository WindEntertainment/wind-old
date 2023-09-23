#include "application.h"

namespace wind {
    namespace system {
        bool Application::isAlive = false;
        vector<std::function<void()>> Application::terminate_event;
        std::function<bool()> Application::quit_event;        

        bool Application::alive() {
            return isAlive;
        }

        void Application::quit() {
            if (!quit_event) {
                isAlive = false;
                return;
            }

            isAlive = !quit_event();
        }

        void Application::init(std::function<bool()> try_quiting) {
            log().info() << "Application initilization...";

            quit_event = try_quiting;

            //============================================================//

            if (!glfwInit()) {
                log().error() << "Fail glfwInit:" << getGLFWError();
                return;
            }

            int major, minor, revision;
            glfwGetVersion(&major, &minor, &revision);
            log().info() << "glfw version:" << major << "." << minor << "." << revision;
        
            //============================================================//

            isAlive = true;
        }

        int Application::terminate() {
            for (auto callback : terminate_event) 
                callback();
            // glfwTerminate() // segmentation fault
            return EXIT_FAILURE;
        }

        void Application::addTerminateCallback(std::function<void()> callback) {
            assert(callback != nullptr);
            terminate_event.push_back(callback);   
        }

        int Application::loop(std::function<void()> update) {
            log().info() << "Start application loop";

            while (alive()) {
                if (update)
                    update();
                glfwPollEvents();
            }

            terminate();
            return EXIT_SUCCESS;
        }
    }
}