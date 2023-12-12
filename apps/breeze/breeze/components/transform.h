#pragma once
#include "../utils.h"

namespace wind {
    namespace breeze {
        struct Transform {
            vec3 position = {0, 0, 0};
            vec3 rotation = {0, 0, 0};
            vec3 scale    = {0, 0, 0};
        };
    }
}