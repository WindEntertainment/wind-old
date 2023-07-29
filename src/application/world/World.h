#include "../mesh/Mesh.h"

namespace app {
    class World {
    public:
        Mesh* mesh = nullptr;
        Shader* shader = nullptr;
    };
}