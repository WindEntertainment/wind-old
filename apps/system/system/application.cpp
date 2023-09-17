#include "application.h"

namespace wind {
    namespace system {
        bool Application::isAlive = false;

        bool Application::alive() {
            return isAlive;
        }

        void Application::quit() {
            isAlive = false;
        }

        void Application::init() {
            log().info() << "Application initilization...";

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

        int Application::loop(std::function<void()> update) {
            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                log().error() << "Failed GLAD load gl loader";
                return EXIT_FAILURE;
            }

            log().info() << "Start application loop";

            while (alive()) {
                if (update)
                    update();
                glfwPollEvents();
            }

            return EXIT_SUCCESS;
        }
    }
}