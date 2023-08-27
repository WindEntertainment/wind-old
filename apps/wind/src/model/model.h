#include "../entity/entity.h"

namespace app {
    struct Model : Component {
        Mesh* mesh     = nullptr;
        Shader* shader = nullptr;

        Model(Mesh* _mesh, Shader* _shader):
            mesh(_mesh), shader(_shader) {};
    };
}