#include "texture.h"

namespace wind {
    namespace renderer {
        uint Texture::id() const {
            return m_texture_id;
        }

        Texture::Texture(unsigned char* _image, int _width, int _height) {
            glGenTextures(1, &m_texture_id);
            glBindTexture(GL_TEXTURE_2D, m_texture_id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        Texture::~Texture() {
            glDeleteTextures(1, &m_texture_id);
        }
    }
}