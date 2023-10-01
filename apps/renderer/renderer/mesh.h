#include "shader.h"
#include "texture.h"

namespace wind {
    namespace renderer {
        struct Mesh {
        private:
            struct Vertex {
                vec3 position;
                vec2 tex_coords;
            };
        private:
            uint m_VAO, m_VBO, m_EBO;
            vector<Vertex> m_vertices;
            vector<uint> m_indices;
        public:
            Texture* m_texture;
            Shader* m_shader = nullptr;

            Mesh(vector<vec3> vertices, vector<uint> indicies, vector<vec2> uv, Texture* texture, Shader* shader);
            ~Mesh();

            uint VAO() const;
            uint size() const;  

            Texture* texture() const;
            Shader* shader() const;
        };
    }
}