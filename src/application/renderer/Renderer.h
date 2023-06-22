#include "../window/Window.h"

namespace app {
    class Renderer {
    private:
        float* vertices;
        GLuint VBO, // vertex buffer object 
               VAO; // vertex array object
    public:
        Renderer();
        ~Renderer();
    };
}