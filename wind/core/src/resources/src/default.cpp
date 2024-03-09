#include "resources/default.h"
#include <cmath>

namespace wind {

static Shader* m_defaultParticleShader = nullptr;
static Shader* m_default2DShader = nullptr;
static Mesh* m_defaultReactangle = nullptr;
static Mesh* m_defaultCircle = nullptr;

void DefaultRes::load() {
    // clang-format off

    m_default2DShader = new Shader(
        R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoords;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            out vec2 TexCoord;

            void main() {
                gl_Position = projection * view * model * vec4(aPos, 1.0);
                TexCoord = aTexCoords;
            }
        )",
        R"(
            #version 330 core
            
            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D tex0;
            uniform vec4 color;

            void main() {
                FragColor = color; 
            }
        )"
    );

    m_defaultParticleShader = new Shader(
        R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoords;
            layout (location = 3) in mat4 model;

            uniform mat4 view;
            uniform mat4 projection;

            out vec2 TexCoord;

            void main() {
                gl_Position = projection * view * model * vec4(aPos, 1.0);
                TexCoord = aTexCoords;
            }
        )",
        R"(
            #version 330 core
            
            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D tex0;
            uniform vec4 color;

            void main() {
                FragColor = color; 
            }
        )"
    );

    m_defaultReactangle = new Mesh( 
        {
            { 0.5f,  0.5f, 0.0f   }, 
            { 0.5f, -0.5f, 0.0f,  },
            { -0.5f,  0.5f, 0.0f, },    
            { -0.5f, -0.5f, 0.0f  }
        },
        {0, 1, 2, 1, 3, 2},
        {
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        }
    );

    {
        vector<vec3> vertices;
        vector<unsigned int> indices;
        vector<vec2> uv;

        const int numSegments = 12;
        const float segmentAngle = 2.f * PI / numSegments;

        vertices.push_back({0, 0, 0});
        uv.push_back({0.5f, 0.5f});

        for (int i = 0; i < numSegments; ++i) {
            float angle = i * segmentAngle;
            float c = cosf(angle),
                  s = sinf(angle);

            vertices.push_back({ c, s, 0.f });
            uv.push_back({
                0.5f + 0.5f * c,
                0.5f + 0.5f * s
            });
        }

        for (int i = 1; i <= numSegments; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back((i % numSegments) + 1);
        }

        m_defaultCircle = new Mesh(vertices, indices, uv);
    }

    // clang-format on
}

void DefaultRes::free() {
    delete m_default2DShader;
    delete m_defaultReactangle;
}

Mesh* DefaultRes::getReactangle() {
    return m_defaultReactangle;
}

Mesh* DefaultRes::getCircle() {
    return m_defaultCircle;
}

Shader* DefaultRes::getParticleShader() {
    return m_defaultParticleShader;
}

Shader* DefaultRes::get2DShader() {
    return m_default2DShader;
}

} // namespace wind