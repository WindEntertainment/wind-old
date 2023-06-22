#include "Shader.h"

namespace app {
    Shader::Shader(const char* _vsh, const char* _fsh) {
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &_vsh, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &_fsh, NULL);
        glCompileShader(fs);

        m_program = glCreateProgram();
        glAttachShader(m_program, fs);
        glAttachShader(m_program, vs);
        glLinkProgram(m_program);
    }

    Shader::~Shader() {
        glDeleteProgram(m_program);
    }

    void Shader::use() {
        glUseProgram(m_program);
    }
}