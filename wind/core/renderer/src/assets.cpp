#include <renderer/assets.hpp>

namespace wind {
template <>
Texture* AssetManager::getAsset(const char* _key) {
  auto image = getAsset<assets::Image>(_key);
  auto texture = new Texture(image->pixels, image->size);
  delete image;
  return texture;
}
} // namespace wind