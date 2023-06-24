#include "../window/Window.h"

namespace app {
    class Renderer {
    private:
        float* m_vertices;
        GLuint m_VBO, // vertex buffer object 
               m_VAO; // vertex array object
        
        Shader* m_shader;
    public:
        Renderer(Shader* shader);
        ~Renderer();

        void draw();
    };
}   