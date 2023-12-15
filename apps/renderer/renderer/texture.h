#include "utils.h"

namespace wind {
    namespace renderer {
        class Texture {
            uint m_texture_id;
        public:
            Texture(unsigned char* image, int width, int height);
            ~Texture();

            uint id() const;
        };
    }
}