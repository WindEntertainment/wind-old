#include <logger/wind_logger.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <functional>

using glm::ivec2;
using glm::ivec3;

namespace wind {
    namespace system {
        const char* getGLFWError();
    }
}