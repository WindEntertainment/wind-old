#pragma once
#include "logger.h"
#include <renderer/texture.h>

#include <Ultralight/RefPtr.h>
#include <Ultralight/Renderer.h>

namespace wind {

namespace ul = ultralight;

class Ultralight {
public:
  static void init();
  static void dispose();

  static void update();
  static void render();

  static Texture* loadView(const std::string& path, const glm::ivec2 size);

private:
  // forced to use two vectors, because if you
  // make a map with ul::RefPtr<View> as a key
  // there will be a segmentation fault
  static std::vector<ul::RefPtr<ul::View>> m_views;
  static std::vector<Texture*> m_textures;

  static ul::RefPtr<ul::Renderer> m_renderer;
  static ULLogger m_logger;
};

} // namespace wind
