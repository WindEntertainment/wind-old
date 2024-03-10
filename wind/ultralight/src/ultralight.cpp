#include <renderer/texture.h>
#include <wind-ultralight/ultralight.h>

#include <AppCore/Platform.h>
#include <Ultralight/Bitmap.h>
#include <Ultralight/Ultralight.h>

namespace wind {

std::vector<ul::RefPtr<ul::View>> Ultralight::m_views;
std::vector<Texture*> Ultralight::m_textures;
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

  for (size_t i = 0; i < m_views.size(); ++i) {
    ul::BitmapSurface* surface = (ul::BitmapSurface*)(m_views[i]->surface());

    if (!surface->dirty_bounds().IsEmpty()) {
      ul::RefPtr<ul::Bitmap> bitmap = surface->bitmap();
      const auto pixels = (unsigned char*)bitmap->LockPixels();
      const auto size = glm::ivec2{bitmap->width(), bitmap->height()};

      m_textures[i]->setPixels(pixels, size);

      bitmap->UnlockPixels();
      surface->ClearDirtyBounds();
    }
  }
}

Texture* Ultralight::loadView(const std::string& _path, const glm::ivec2 _size) {
  ul::ViewConfig view_config;
  view_config.is_accelerated = false;

  ul::RefPtr<ul::View> view = m_renderer->CreateView(_size.x, _size.y, view_config, nullptr);
  view->LoadURL(("file:///" + _path).c_str());
  m_views.push_back(view);

  Texture* texture = new Texture(nullptr, _size);
  m_textures.push_back(texture);

  assert(m_views.size() == m_textures.size());
  return texture;
};

}; // namespace wind
