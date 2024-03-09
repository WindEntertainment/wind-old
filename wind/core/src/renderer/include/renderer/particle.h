#pragma once
#include <utils/utils.h>

namespace wind {

struct ParticleSystem {
public:
    vec2 position;
    vec2 rotation;
    vec2 scale;

    ParticleSystem(vector<vec3> vertices, vector<uint> indicies,
                   vector<vec2> uv, size_t count);
    ~ParticleSystem();

    uint vao() const;
    uint size() const;
    void draw(glm::mat4 _orthoMatrix, glm::mat4 _viewMatrix);

    void setPosition(uint _i, vec2 position);

private:
    struct Vertex {
        vec3 position;
        vec2 tex_coords;
    };

    uint m_VAO, m_VBO, m_EBO, m_MBO;
    vector<Vertex> m_vertices;
    vector<uint> m_indices;

    vector<glm::mat4> m_models;
};

} // namespace wind