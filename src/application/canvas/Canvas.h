#include "../window/Window.h"

namespace app {
    class Canvas {
    private:
        float* m_vertices;
        GLuint m_VBO, // vertex buffer object 
               m_VAO; // vertex array object
        
        Shader* m_shader;
        float* m_canvas;
    public:
        Canvas(Shader* shader);
        ~Canvas();

        void draw();

        void wall(int x, float height);
    };
}   