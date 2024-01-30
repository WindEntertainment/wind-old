#include <utils/utils.h>

namespace wind {
namespace renderer {

class Shader {
private:
    uint m_program;

public:
    Shader(const char *vertex_shader_text, const char *fragment_shader_text);
    ~Shader();

    void use();

    void uMat4f(const char *name, glm::mat4 mat);
    void uFloatArray(const char *name, size_t size, float *array);
    void uInt(const char *name, int i);
    void uVec2f(const char *name, vec2 vec);
};

} // namespace renderer
} // namespace wind