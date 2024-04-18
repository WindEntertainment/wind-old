#pragma once
#include "Ultralight/Listener.h"

#include "Ultralight/MouseEvent.h"
#include "filesystem.hpp"
#include "input-system/context.h"
#include "input-system/keys.h"
#include "logger.h"

#include <renderer/texture.hpp>

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

  static void triggerScrollEvent(wind::InputSystemContext* context);
  static void triggerMoveEvent(wind::InputSystemContext* context);
  static void triggerCharEvent(wind::InputSystemContext* context);
  static void triggerMousePressEvent(wind::InputSystemContext* context);
  static void triggerMouseReleaseEvent(wind::InputSystemContext* context);
  static void triggerKeyPressEvent(wind::InputSystemContext* context);
  static void triggerKeyHoldEvent(wind::InputSystemContext* context);
  static void triggerKeyReleaseEvent(wind::InputSystemContext* context);

  static Texture* loadView(const std::string& path, const glm::ivec2 size);

  static spdlog::level::level_enum mapUltralightLogLevelToSpd(ul::MessageLevel level);

private:
  // forced to use two vectors, because if you
  // make a map with ul::RefPtr<View> as a key
  // there will be a segmentation fault
  static std::vector<ul::RefPtr<ul::View>> m_views;
  static std::vector<Texture*> m_textures;

  static ul::RefPtr<ul::Renderer> m_renderer;
  static ULLogger m_logger;

  static int glfwModsToUltralightMods(int mods);

  static int keycodeToUltralightKeyCode(KEYCODES key);
  static ul::MouseEvent::Button keycodeToUltralightButtonCode(KEYCODES key);
};

} // namespace wind
