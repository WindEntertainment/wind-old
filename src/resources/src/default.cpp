#include "resources/default.h"

namespace wind {

static Shader* m_default2DShader = nullptr;
static Mesh* m_defaultReactangle = nullptr;

void DefaultRes::load() {
    // clang-format off
    m_default2DShader = new Shader(
        R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoord;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            out vec2 TexCoord;

            void main() {
                gl_Position = vec4(aPos, 1.0);
                TexCoord = aTexCoord;
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

    // clang-format on
}

void DefaultRes::free() {
    delete m_default2DShader;
    delete m_defaultReactangle;
}

Mesh* DefaultRes::getReactangle() {
    return m_defaultReactangle;
}

Shader* DefaultRes::get2DShader() {
    return m_default2DShader;
}

} // namespace wind