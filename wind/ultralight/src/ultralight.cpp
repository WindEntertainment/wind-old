#include "AppCore/Platform.h"
#include "Ultralight/Bitmap.h"
#include "renderer/texture.h"
#include "utils/ext_string.h"
#include <glm/ext/scalar_uint_sized.hpp>
#include <wind-ultralight/ultralight.h>

namespace wind {

std::map<const char*, ul::RefPtr<ul::View>> Ultralight::m_views;
std::map<const char*, Texture*> Ultralight::m_textures;
ul::RefPtr<ul::Renderer> Ultralight::m_renderer;

void Ultralight::init() {
  // Init config
  ul::Config config;
  ul::Platform::instance().set_config(config);

  // Init platform
  ul::Platform::instance().set_font_loader(ul::GetPlatformFontLoader());
  ul::Platform::instance().set_file_system(ul::GetPlatformFileSystem("./assets"));
  ul::Platform::instance().set_logger(ul::GetDefaultLogger("ultralight.log"));

  // Create Renderer
  m_renderer = ul::Renderer::Create();
}

void Ultralight::update() {
  m_renderer->Update();
}

void Ultralight::render() {
  m_renderer->Render();

  std::for_each(m_views.begin(), m_views.end(), [](auto view) {
    ul::BitmapSurface* surface = (ul::BitmapSurface*)(view.second->surface());

    if (!surface->dirty_bounds().IsEmpty()) {
      ul::RefPtr<ul::Bitmap> bitmap = surface->bitmap();
      const auto pixels = (unsigned char*)bitmap->LockPixels();
      const auto size = glm::ivec2{bitmap->width(), bitmap->height()};

      if (m_textures.contains(view.first))
        m_textures[view.first]->setPixels(pixels, size);
      else
        m_textures[view.first] = new Texture(pixels, size);

      bitmap->UnlockPixels();
      surface->ClearDirtyBounds();
    }
  });
}

Texture* Ultralight::loadView(const std::string& _path) {
  ul::ViewConfig view_config;
  view_config.is_accelerated = false;

  ul::RefPtr<ul::View> view = m_renderer->CreateView(800, 600, view_config, nullptr);

  view->LoadURL(("file:///" + _path).c_str());

  m_views.insert(std::make_pair(_path.c_str(), view));

  render();
  return m_textures[_path.c_str()];
};

}; // namespace wind
