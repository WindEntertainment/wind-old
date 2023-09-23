#include "shader.h"
#include "texture.h"

namespace wind {
    namespace renderer {
        struct Mesh {
        private:
            uint m_VAO, m_VBO, m_EBO;
            vector<vec3> m_vertices;
            vector<uint> m_indices;

            Shader* m_shader = nullptr;

        public:
            Mesh(vector<vec3> vertices, vector<uint> indicies, Shader* shader);
            ~Mesh();

            uint VAO() const;
            uint size() const;  

            Shader* shader() const;
        };
    }
}