#include "Shader.h"

namespace app {
    Shader::Shader(const char* _vsh, const char* _fsh) {
        int  success;
        char msg[512];

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &_vsh, NULL);
        glCompileShader(vs);

        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vs, 512, NULL, msg);
            throw std::invalid_argument(
                "Failed compile vertex shader:" + string(msg)
            );
        }

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &_fsh, NULL);
        glCompileShader(fs);

        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fs, 512, NULL, msg);
            throw std::invalid_argument(
                "Failed compile fragment shader:" + string(msg)
            );
        }

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