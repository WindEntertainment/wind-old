#include "../event-handlers/KeyEventHandler.h"

namespace app {

    class Shader {
    private:
        GLuint m_program;
    public:
        Shader() {};
        Shader(const char* vertex_shader_text, const char* fragment_shader_text);
        ~Shader();

        void use();
    };

}