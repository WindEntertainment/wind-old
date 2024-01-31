#pragma once
#include <utils/utils.h>

namespace wind {

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
    Mesh(vector<vec3> vertices, vector<uint> indicies, vector<vec2> uv);
    ~Mesh();

    uint vao() const;
    uint size() const;
};

} // namespace wind