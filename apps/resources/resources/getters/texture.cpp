#include "texture.h"
#include <asset-bundler/objects/image.h>

namespace wind {
    namespace resources {
        template <>
        renderer::Texture* get(const char* _name) {
            auto image = get<assets::Image>(_name);
            if (!image)
                return nullptr;
            
            auto res = new renderer::Texture(
                image->data, image->width, image->height
            );

            delete image;

            return res;
        }
    }
}