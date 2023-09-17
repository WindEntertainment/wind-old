#include "mesh.h"

namespace wind {
    namespace renderer {
        class Renderer {
        public:
            void clear();
            void render(Mesh* mesh, vec3 position, vec3 rotation); 
        };
    }
}