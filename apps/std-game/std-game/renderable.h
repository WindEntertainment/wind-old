#pragma once
#include "utils.h"

namespace wind {
    namespace stdgame {
        struct Renderable {
            renderer::Mesh* mesh;
            renderer::Texture* texture;
            renderer::Shader* shader;
            vec2 tiling;
        };
        
    }
}