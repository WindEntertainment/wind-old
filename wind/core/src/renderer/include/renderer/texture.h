#pragma once
#include <utils/utils.h>

namespace wind {
class Texture {
public:
  Texture(const unsigned char* pixels, const glm::ivec2 size);
  ~Texture();

  void setPixels(const unsigned char* pixels, const glm::ivec2 size);
  uint id() const;

private:
  uint m_texture_id = 0;
};

} // namespace wind
