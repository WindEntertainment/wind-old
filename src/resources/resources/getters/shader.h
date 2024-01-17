#pragma once
#include "../resource_manager.h"
#include <renderer/renderer.h>

namespace wind {
    namespace resources {
        template <>
        renderer::Shader* get(const char* _name);
    }
}