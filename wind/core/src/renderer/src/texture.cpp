/*
//  dice.jpg
_image = new unsigned char[11*3]{
        24, 14, 139,
        28, 22, 180 ,
        6, 17, 135 ,
        255, 255, 255,
        210, 251, 84,
        13, 10, 163 ,
        33, 37, 194,
        255, 255, 255,
        193, 173, 42 ,
        252, 249, 46 ,
        246, 250, 33,
};
*/

#include "renderer/texture.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/scalar_uint_sized.hpp>
// clang-formaton

namespace wind {

uint Texture::id() const {
    return m_texture_id;
}

Texture::Texture(unsigned char* _pixels, int _width, int _height) {
    static bool is_created = false;
    if (!is_created) {
        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        is_created = true;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, _pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture_id);
}

} // namespace wind
