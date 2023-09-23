#include "image_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace wind {
    namespace assets {
            ISerializable* ImageLoader::load(fs::path _path) {
                int width, height, channels;
                
                unsigned char* image =
                    stbi_load(_path.c_str(), &width, &height, &channels, 0);
                if (image == nullptr) {
                    log().error() << "ImageLoader: " << stbi_failure_reason() << " by path: [" << _path << "]";
                    return nullptr;
                }

                Image* out = new Image(); {
                    out->data = image;                
                    out->width = width;
                    out->height = height;
                    out->channels = channels;
                }

                return out;
            }
    }
}