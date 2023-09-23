#include "utils.h"

namespace wind {
    namespace renderer {
        struct Camera {
            glm::vec3 position{0, 0, 0};
            glm::vec3 front{0, 0, 0};
            glm::vec3 up{0, 1, 0};
        };
    }
}