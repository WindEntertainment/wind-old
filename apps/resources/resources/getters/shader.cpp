#include "shader.h"
#include <asset-bundler/objects/shader.h>

namespace wind {
    namespace resources {
        template <>
        renderer::Shader* get(const char* _name) {
            auto source = get<assets::Shader>(_name);
            if (!source)
                return nullptr;
            
            auto res = new renderer::Shader(
                source->vtx.c_str(), source->fgt.c_str()
            );

            delete source;

            return res;
        }
    }
}