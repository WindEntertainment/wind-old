#pragma once
#include "Ultralight/RefPtr.h"
#include "Ultralight/Renderer.h"
#include <AppCore/Platform.h>
#include <Ultralight/Bitmap.h>
#include <Ultralight/Ultralight.h>
#include <map>

#include <renderer/texture.h>

namespace wind {

namespace ul = ultralight;

class Ultralight {
public:
  static void init();
  static void dispose();

  static void update();
  static void render();

  static Texture* loadView(const std::string& path);

private:
  static std::map<const char*, ul::RefPtr<ul::View>> m_views;
  static std::map<const char*, Texture*> m_textures;
  static ul::RefPtr<ul::Renderer> m_renderer;
};

} // namespace wind
