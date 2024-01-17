#include "utils.h"

namespace wind {
    namespace renderer {
        struct Camera {
            glm::vec3 position;
            glm::vec3 front;
            glm::vec3 up;
        };
    }
}