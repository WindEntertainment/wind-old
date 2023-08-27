#include "../event-handlers/key_event_handler.h"

namespace app {

    class Shader {
    private:
        GLuint m_program;
    public:
        Shader(const char* vertex_shader_text, const char* fragment_shader_text);
        ~Shader();

        void use();

        void uMat4f(const char* name, glm::mat4 mat);
        void uFloatArray(const char* name, size_t size, float* array);
    };

}