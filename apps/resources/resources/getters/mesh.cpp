#include "mesh.h"
#include <asset-bundler/objects/mesh.h>

namespace wind {
    namespace resources {
        template <>
        renderer::Mesh* get(const char* _name) {
            auto source = get<assets::Mesh>(_name);
            if (!source)
                return nullptr;
            
            auto res = new renderer::Mesh(
                source->vertices, source->indices, source->uv,
                nullptr, nullptr
            );
 
            delete source;

            return res;
        }
    }
}