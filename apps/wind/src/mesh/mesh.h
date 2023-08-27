#include "../window/window.h"

namespace app {
    class Mesh {
    private:
        std::vector<vec3> m_vertices;
        std::vector<uint> m_indices;

        uint m_VAO, m_VBO, m_EBO;
    public:
        Mesh(std::vector<vec3> vertices, std::vector<uint> indices);
        ~Mesh();

        uint VAO();
        uint size();
    };
}