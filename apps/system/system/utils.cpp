#include "utils.h"

namespace wind {
    namespace system {
        const char* getGLFWError() {
            const char* description;
            glfwGetError(&description);
            return description;
        }
    }
}