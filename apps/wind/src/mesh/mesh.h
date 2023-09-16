#pragma once
#include "../entity/entity.h"
#include <asset-bundler/objects/mesh.h>

namespace wind {
    struct Mesh : public Component {
    private:
        uint m_VAO, m_VBO, m_EBO;
        assets::Mesh* m_mesh;
    public:
        Shader* shader = nullptr;
    public:
        Mesh(assets::Mesh* mesh, Shader* shader);
        ~Mesh();

        uint VAO();
        uint size();
    };
}