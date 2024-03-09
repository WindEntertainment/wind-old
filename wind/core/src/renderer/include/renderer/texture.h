#pragma once
#include <utils/utils.h>

namespace wind {
class Texture {
  uint m_texture_id;

public:
  Texture(unsigned char* image, int width, int height);
  ~Texture();

  uint id() const;
};
} // namespace wind
