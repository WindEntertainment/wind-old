#include "Shader.h"

namespace app {
    Shader::Shader(const char* _vsh, const char* _fsh) {
        int  success;
        char msg[512];


        // Vertex
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

        // Fragment 
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

        // Program
        m_program = glCreateProgram();
        glAttachShader(m_program, fs);
        glAttachShader(m_program, vs);
        glLinkProgram(m_program);

        glGetShaderiv(m_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_program, 512, NULL, msg);
            throw std::invalid_argument(
                "Failed link shader:" + string(msg)
            );
        }

        glDeleteShader(vs);
        glDeleteShader(fs); 
    }

    Shader::~Shader() {
        glDeleteProgram(m_program);
    }

    void Shader::use() {
        glUseProgram(m_program);
    }

    void Shader::uFloatArray(const char* _name, size_t _size, float* _arr) {
        int loc = glGetUniformLocation(m_program, _name);
        glUniform1fv(loc, _size, _arr);
    }
}