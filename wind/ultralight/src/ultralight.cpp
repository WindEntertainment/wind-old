#ifdef __APPLE__
#include "Ultralight/ConsoleMessage.h"
#endif

#include "Ultralight/KeyEvent.h"
#include "Ultralight/Listener.h"
#include "Ultralight/MouseEvent.h"
#include "input-system/keys.h"
#include <algorithm>
#include <renderer/texture.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <wind-ultralight/ultralight.h>

#include <AppCore/Platform.h>
#include <Ultralight/Bitmap.h>
#include <Ultralight/Ultralight.h>

namespace wind {

class ViewLogger : public ul::ViewListener {
private:
  inline std::string toUTF8(const ul::String& str) {
    ul::String8 utf8 = str.utf8();
    return std::string(utf8.data(), utf8.length());
  }

  inline const char* stringify(ul::MessageSource source) {
    switch (source) {
    case ul::kMessageSource_XML:
      return "XML";
    case ul::kMessageSource_JS:
      return "JS";
    case ul::kMessageSource_Network:
      return "Network";
    case ul::kMessageSource_ConsoleAPI:
      return "ConsoleAPI";
    case ul::kMessageSource_Storage:
      return "Storage";
    case ul::kMessageSource_AppCache:
      return "AppCache";
    case ul::kMessageSource_Rendering:
      return "Rendering";
    case ul::kMessageSource_CSS:
      return "CSS";
    case ul::kMessageSource_Security:
      return "Security";
    case ul::kMessageSource_ContentBlocker:
      return "ContentBlocker";
    case ul::kMessageSource_Other:
      return "Other";
    default:
      return "";
    }
  }

  inline const char* stringify(ul::MessageLevel level) {
    switch (level) {
    case ul::kMessageLevel_Log:
      return "Log";
    case ul::kMessageLevel_Warning:
      return "Warning";
    case ul::kMessageLevel_Error:
      return "Error";
    case ul::kMessageLevel_Debug:
      return "Debug";
    case ul::kMessageLevel_Info:
      return "Info";
    default:
      return "";
    }
  }

public:
#ifdef __APPLE__
  void OnAddConsoleMessage(
    ul::View* caller,
    const ul::ConsoleMessage& log) override {

    auto source = log.source();
    auto level = log.level();
    auto message = log.message();
    auto source_id = log.source_id();
    auto line_number = log.line_number();
    auto column_number = log.column_number();

    spdlog::log(Ultralight::mapUltralightLogLevelToSpd(level), "[UL::Console]: [{}] {}", stringify(source), toUTF8(message));

    if (source == ul::kMessageSource_JS)
      spdlog::log(Ultralight::mapUltralightLogLevelToSpd(level), "[UL::Console]: ({}) @ line: {}, column: {})", toUTF8(source_id), line_number, column_number);

    std::cout << std::endl;
  }
#else
  void OnAddConsoleMessage(
    ul::View* caller,
    ul::MessageSource source,
    ul::MessageLevel level,
    const ul::String& message,
    uint32_t line_number,
    uint32_t column_number,
    const ul::String& source_id) {

    spdlog::log(Ultralight::mapUltralightLogLevelToSpd(level), "[Console]: [{}] {}", stringify(source), toUTF8(message));

    if (source == ul::kMessageSource_JS) {
      spdlog::log(Ultralight::mapUltralightLogLevelToSpd(level), "({}) @ line: {}, column: {})", toUTF8(source_id), line_number, column_number);
    }

    std::cout << std::endl;
  }
#endif
};

class LoadLogger : public ul::LoadListener {
public:
  void OnBeginLoading(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) override {
    spdlog::info("[UL::Loader]: Loading started, url: {}", url.utf8().data());
  }

  void OnFinishLoading(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) override {
    spdlog::info("[UL::Loader]: Loading finished, url: {}", url.utf8().data());
  }

  void OnFailLoading(
    ul::View* caller, uint64_t frame_id, bool is_main_frame,
    const ul::String& url, const ul::String& description,
    const ul::String& error_domain, int error_code) override {
    spdlog::log(
      spdlog::level::err,
      "[UL::Loader]: Loading failed, error code: {}, description: {}, error domain: {}, url: {}",
      error_code,
      description.utf8().data(),
      error_domain.utf8().data(),
      url.utf8().data());
  }

  void OnDOMReady(ul::View* caller, uint64_t frame_id, bool is_main_frame, const ul::String& url) override {
    spdlog::info("[UL::Loader]: DOM ready, url: {}", url.utf8().data());
  }
};

#ifdef __APPLE__
class NetworkLogger : public ul::NetworkListener {
public:
  bool OnNetworkRequest(ultralight::View* caller, ul::NetworkRequest& request) override {
    spdlog::info("[UL::Network]: {} request, url: {}", request.url().utf8().data(), request.httpMethod().utf8().data());
    return true;
  };
};
#endif

std::vector<ul::RefPtr<ul::View>>
  Ultralight::m_views;
std::vector<Texture*> Ultralight::m_textures;

ul::RefPtr<ul::Renderer> Ultralight::m_renderer;
ULLogger Ultralight::m_logger;
ULFileSystem m_fileSystem;

void Ultralight::init() {
  // Init config
  ul::Config config;
  ul::Platform::instance().set_config(config);

  // Init platform
  ul::Platform::instance().set_font_loader(ul::GetPlatformFontLoader());
  ul::Platform::instance().set_file_system(&m_fileSystem);
  ul::Platform::instance().set_logger(&m_logger);

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

void Ultralight::triggerMousePressEvent(wind::InputSystemContext* context) {
  std::for_each(context->mouseContext.pressedButtons.begin(), context->mouseContext.pressedButtons.end(), [&context](auto pressedButton) {
    ul::MouseEvent evt;
    evt.type = ul::MouseEvent::Type::kType_MouseDown;
    // TODO: handle move events
    evt.x = context->mouseContext.cursorX;
    evt.y = context->mouseContext.cursorY;
    evt.button = keycodeToUltralightButtonCode(pressedButton);

    std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireMouseEvent(evt); });
  });
}

void Ultralight::triggerMouseReleaseEvent(wind::InputSystemContext* context) {
  std::for_each(context->mouseContext.releasedButtons.begin(), context->mouseContext.releasedButtons.end(), [&context](auto releasedButton) {
    ul::MouseEvent evt;
    evt.type = ul::MouseEvent::Type::kType_MouseUp;
    // TODO: handle move events
    evt.x = context->mouseContext.cursorX;
    evt.y = context->mouseContext.cursorY;
    evt.button = keycodeToUltralightButtonCode(releasedButton);

    std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireMouseEvent(evt); });
  });
}

void Ultralight::triggerKeyPressEvent(wind::InputSystemContext* context) {
  std::for_each(context->keyboardContext.pressedKeys.begin(), context->keyboardContext.pressedKeys.end(), [](auto pressedKey) {
    ul::KeyEvent evt;
    evt.type = ul::KeyEvent::kType_RawKeyDown;
    evt.virtual_key_code = keycodeToUltralightKeyCode(pressedKey);
    // TODO: add modifiers
    // evt.modifiers = 0;
    GetKeyIdentifierFromVirtualKeyCode(evt.virtual_key_code, evt.key_identifier);

    std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireKeyEvent(evt); });
  });
}

void Ultralight::triggerKeyHoldEvent(wind::InputSystemContext* context) {
  std::for_each(context->keyboardContext.heldKeys.begin(), context->keyboardContext.heldKeys.end(), [](auto heldKey) {
    ul::KeyEvent evt;
    evt.type = ul::KeyEvent::kType_KeyDown;
    evt.virtual_key_code = keycodeToUltralightKeyCode(heldKey);
    // TODO: add modifiers
    // evt.modifiers = 0;
    GetKeyIdentifierFromVirtualKeyCode(evt.virtual_key_code, evt.key_identifier);

    std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireKeyEvent(evt); });
  });
}

void Ultralight::triggerKeyReleaseEvent(wind::InputSystemContext* context) {
  std::for_each(context->keyboardContext.releasedKeys.begin(), context->keyboardContext.releasedKeys.end(), [](auto releasedKey) {
    ul::KeyEvent evt;
    evt.type = ul::KeyEvent::kType_KeyUp;
    evt.virtual_key_code = keycodeToUltralightKeyCode(releasedKey);
    // TODO: add modifiers
    // evt.modifiers = 0;
    GetKeyIdentifierFromVirtualKeyCode(evt.virtual_key_code, evt.key_identifier);

    std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireKeyEvent(evt); });
  });
}

void Ultralight::triggerCharEvent(wind::InputSystemContext* context) {
  if (context->keyboardContext.codepoint == '`')
    return;

  ultralight::KeyEvent evt;
  evt.type = ultralight::KeyEvent::kType_Char;

  ultralight::String text = ultralight::String32((const char32_t*)&context->keyboardContext.codepoint, 1);

  evt.text = text;
  evt.unmodified_text = text;

  std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireKeyEvent(evt); });
}

void Ultralight::triggerScrollEvent(wind::InputSystemContext* context) {
  ultralight::ScrollEvent evt;
  evt.type = ultralight::ScrollEvent::kType_ScrollByPixel;
  evt.delta_x = context->mouseContext.scrollX * 32;
  evt.delta_y = context->mouseContext.scrollY * 32;

  std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireScrollEvent(evt); });
}

void Ultralight::triggerMoveEvent(wind::InputSystemContext* context) {
  std::for_each(context->mouseContext.pressedButtons.begin(), context->mouseContext.pressedButtons.end(), [&context](auto pressedButton) {
    ultralight::MouseEvent evt;
    evt.type = ultralight::MouseEvent::kType_MouseMoved;
    evt.x = context->mouseContext.cursorX;
    evt.y = context->mouseContext.cursorY;
    evt.button = keycodeToUltralightButtonCode(pressedButton);

    std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireMouseEvent(evt); });
  });

  if (context->mouseContext.pressedButtons.empty()) {
    ultralight::MouseEvent evt;
    evt.type = ultralight::MouseEvent::kType_MouseMoved;
    evt.x = context->mouseContext.cursorX;
    evt.y = context->mouseContext.cursorY;

    std::for_each(m_views.begin(), m_views.end(), [evt](ul::RefPtr<ul::View> view) { view->FireMouseEvent(evt); });
  }
}

Texture* Ultralight::loadView(const std::string& _path, const glm::ivec2 _size) {
  ul::ViewConfig view_config;
  view_config.is_accelerated = false;

  ul::RefPtr<ul::View>
    view = m_renderer->CreateView(_size.x, _size.y, view_config, nullptr);

  view->set_view_listener(new ViewLogger());
  view->set_load_listener(new LoadLogger());
#ifdef __APPLE__
  view->set_network_listener(new NetworkLogger());
#endif

  // view->LoadURL(("file:///" + _path).c_str());
  ultralight::String url("http://localhost:5174"); // Change the URL to match your custom server
  view->LoadURL(url);

  m_views.push_back(view);

  Texture* texture = new Texture(nullptr, _size);
  m_textures.push_back(texture);

  assert(m_views.size() == m_textures.size());
  return texture;
};

// ul::MouseEvent::Type Ultralight::keyToMouseEventType(KEYCODES key) {
//   if (
//     key.keycode > KEYCODES::MOUSE_START &&
//     key.keycode < KEYCODES::MOUSE_END) {
//     return ul::MouseEvent::kType_MouseDown;
//   }

//   if (
//     key.keycode > KEYCODES::MOUSE_START &&
//     key.keycode < KEYCODES::MOUSE_END) {
//     return ul::MouseEvent::kType_MouseUp;
//   }

//   return ul::MouseEvent::kType_MouseUp;
// }

// ul::KeyEvent::Type Ultralight::keyToKeyEventType(Key key) {
//   if (
//     key.keycode > KEYCODES::KEYBOARD_START &&
//     key.keycode < KEYCODES::KEYBOARD_END) {
//     return ul::KeyEvent::kType_KeyDown;
//   }

//   if (
//     key.keycode > KEYCODES::KEYBOARD_START &&
//     key.keycode < KEYCODES::KEYBOARD_END) {
//     return ul::KeyEvent::kType_KeyUp;
//   }

//   return ul::KeyEvent::kType_KeyUp;
// }

spdlog::level::level_enum Ultralight::mapUltralightLogLevelToSpd(ul::MessageLevel level) {
  switch (level) {
  case ul::MessageLevel::kMessageLevel_Log:
    return spdlog::level::info;
  case ul::MessageLevel::kMessageLevel_Warning:
    return spdlog::level::warn;
  case ul::MessageLevel::kMessageLevel_Error:
    return spdlog::level::err;
  case ul::MessageLevel::kMessageLevel_Debug:
    return spdlog::level::debug;
  case ul::MessageLevel::kMessageLevel_Info:
    return spdlog::level::info;
  }
}

int Ultralight::glfwModsToUltralightMods(int mods) {
  int result = 0;
  if (mods & GLFW_MOD_ALT)
    result |= ul::KeyEvent::kMod_AltKey;
  if (mods & GLFW_MOD_CONTROL)
    result |= ul::KeyEvent::kMod_CtrlKey;
  if (mods & GLFW_MOD_SUPER)
    result |= ul::KeyEvent::kMod_MetaKey;
  if (mods & GLFW_MOD_SHIFT)
    result |= ul::KeyEvent::kMod_ShiftKey;
  return result;
}

int Ultralight::keycodeToUltralightKeyCode(KEYCODES key) {
  switch (key) {
  case KEYCODES::KEY_SPACE:
    return ul::KeyCodes::GK_SPACE;
  case KEYCODES::KEY_APOSTROPHE:
    return ul::KeyCodes::GK_OEM_7;
  case KEYCODES::KEY_COMMA:
    return ul::KeyCodes::GK_OEM_COMMA;
  case KEYCODES::KEY_MINUS:
    return ul::KeyCodes::GK_OEM_MINUS;
  case KEYCODES::KEY_PERIOD:
    return ul::KeyCodes::GK_OEM_PERIOD;
  case KEYCODES::KEY_SLASH:
    return ul::KeyCodes::GK_OEM_2;
  case KEYCODES::KEY_0:
    return ul::KeyCodes::GK_0;
  case KEYCODES::KEY_1:
    return ul::KeyCodes::GK_1;
  case KEYCODES::KEY_2:
    return ul::KeyCodes::GK_2;
  case KEYCODES::KEY_3:
    return ul::KeyCodes::GK_3;
  case KEYCODES::KEY_4:
    return ul::KeyCodes::GK_4;
  case KEYCODES::KEY_5:
    return ul::KeyCodes::GK_5;
  case KEYCODES::KEY_6:
    return ul::KeyCodes::GK_6;
  case KEYCODES::KEY_7:
    return ul::KeyCodes::GK_7;
  case KEYCODES::KEY_8:
    return ul::KeyCodes::GK_8;
  case KEYCODES::KEY_9:
    return ul::KeyCodes::GK_9;
  case KEYCODES::KEY_SEMICOLON:
    return ul::KeyCodes::GK_OEM_1;
  case KEYCODES::KEY_EQUAL:
    return ul::KeyCodes::GK_OEM_PLUS;
  case KEYCODES::KEY_A:
    return ul::KeyCodes::GK_A;
  case KEYCODES::KEY_B:
    return ul::KeyCodes::GK_B;
  case KEYCODES::KEY_C:
    return ul::KeyCodes::GK_C;
  case KEYCODES::KEY_D:
    return ul::KeyCodes::GK_D;
  case KEYCODES::KEY_E:
    return ul::KeyCodes::GK_E;
  case KEYCODES::KEY_F:
    return ul::KeyCodes::GK_F;
  case KEYCODES::KEY_G:
    return ul::KeyCodes::GK_G;
  case KEYCODES::KEY_H:
    return ul::KeyCodes::GK_H;
  case KEYCODES::KEY_I:
    return ul::KeyCodes::GK_I;
  case KEYCODES::KEY_J:
    return ul::KeyCodes::GK_J;
  case KEYCODES::KEY_K:
    return ul::KeyCodes::GK_K;
  case KEYCODES::KEY_L:
    return ul::KeyCodes::GK_L;
  case KEYCODES::KEY_M:
    return ul::KeyCodes::GK_M;
  case KEYCODES::KEY_N:
    return ul::KeyCodes::GK_N;
  case KEYCODES::KEY_O:
    return ul::KeyCodes::GK_O;
  case KEYCODES::KEY_P:
    return ul::KeyCodes::GK_P;
  case KEYCODES::KEY_Q:
    return ul::KeyCodes::GK_Q;
  case KEYCODES::KEY_R:
    return ul::KeyCodes::GK_R;
  case KEYCODES::KEY_S:
    return ul::KeyCodes::GK_S;
  case KEYCODES::KEY_T:
    return ul::KeyCodes::GK_T;
  case KEYCODES::KEY_U:
    return ul::KeyCodes::GK_U;
  case KEYCODES::KEY_V:
    return ul::KeyCodes::GK_V;
  case KEYCODES::KEY_W:
    return ul::KeyCodes::GK_W;
  case KEYCODES::KEY_X:
    return ul::KeyCodes::GK_X;
  case KEYCODES::KEY_Y:
    return ul::KeyCodes::GK_Y;
  case KEYCODES::KEY_Z:
    return ul::KeyCodes::GK_Z;
  case KEYCODES::KEY_LEFT_BRACKET:
    return ul::KeyCodes::GK_OEM_4;
  case KEYCODES::KEY_BACKSLASH:
    return ul::KeyCodes::GK_OEM_5;
  case KEYCODES::KEY_RIGHT_BRACKET:
    return ul::KeyCodes::GK_OEM_6;
  case KEYCODES::KEY_GRAVE_ACCENT:
    return ul::KeyCodes::GK_OEM_3;
  case KEYCODES::KEY_WORLD_1:
    return ul::KeyCodes::GK_UNKNOWN;
  case KEYCODES::KEY_WORLD_2:
    return ul::KeyCodes::GK_UNKNOWN;
  case KEYCODES::KEY_ESCAPE:
    return ul::KeyCodes::GK_ESCAPE;
  case KEYCODES::KEY_ENTER:
    return ul::KeyCodes::GK_RETURN;
  case KEYCODES::KEY_TAB:
    return ul::KeyCodes::GK_TAB;
  case KEYCODES::KEY_BACKSPACE:
    return ul::KeyCodes::GK_BACK;
  case KEYCODES::KEY_INSERT:
    return ul::KeyCodes::GK_INSERT;
  case KEYCODES::KEY_DELETE:
    return ul::KeyCodes::GK_DELETE;
  case KEYCODES::KEY_RIGHT:
    return ul::KeyCodes::GK_RIGHT;
  case KEYCODES::KEY_LEFT:
    return ul::KeyCodes::GK_LEFT;
  case KEYCODES::KEY_DOWN:
    return ul::KeyCodes::GK_DOWN;
  case KEYCODES::KEY_UP:
    return ul::KeyCodes::GK_UP;
  case KEYCODES::KEY_PAGE_UP:
    return ul::KeyCodes::GK_PRIOR;
  case KEYCODES::KEY_PAGE_DOWN:
    return ul::KeyCodes::GK_NEXT;
  case KEYCODES::KEY_HOME:
    return ul::KeyCodes::GK_HOME;
  case KEYCODES::KEY_END:
    return ul::KeyCodes::GK_END;
  case KEYCODES::KEY_CAPS_LOCK:
    return ul::KeyCodes::GK_CAPITAL;
  case KEYCODES::KEY_SCROLL_LOCK:
    return ul::KeyCodes::GK_SCROLL;
  case KEYCODES::KEY_NUM_LOCK:
    return ul::KeyCodes::GK_NUMLOCK;
  case KEYCODES::KEY_PRINT_SCREEN:
    return ul::KeyCodes::GK_SNAPSHOT;
  case KEYCODES::KEY_PAUSE:
    return ul::KeyCodes::GK_PAUSE;
  case KEYCODES::KEY_F1:
    return ul::KeyCodes::GK_F1;
  case KEYCODES::KEY_F2:
    return ul::KeyCodes::GK_F2;
  case KEYCODES::KEY_F3:
    return ul::KeyCodes::GK_F3;
  case KEYCODES::KEY_F4:
    return ul::KeyCodes::GK_F4;
  case KEYCODES::KEY_F5:
    return ul::KeyCodes::GK_F5;
  case KEYCODES::KEY_F6:
    return ul::KeyCodes::GK_F6;
  case KEYCODES::KEY_F7:
    return ul::KeyCodes::GK_F7;
  case KEYCODES::KEY_F8:
    return ul::KeyCodes::GK_F8;
  case KEYCODES::KEY_F9:
    return ul::KeyCodes::GK_F9;
  case KEYCODES::KEY_F10:
    return ul::KeyCodes::GK_F10;
  case KEYCODES::KEY_F11:
    return ul::KeyCodes::GK_F11;
  case KEYCODES::KEY_F12:
    return ul::KeyCodes::GK_F12;
  case KEYCODES::KEY_F13:
    return ul::KeyCodes::GK_F13;
  case KEYCODES::KEY_F14:
    return ul::KeyCodes::GK_F14;
  case KEYCODES::KEY_F15:
    return ul::KeyCodes::GK_F15;
  case KEYCODES::KEY_F16:
    return ul::KeyCodes::GK_F16;
  case KEYCODES::KEY_F17:
    return ul::KeyCodes::GK_F17;
  case KEYCODES::KEY_F18:
    return ul::KeyCodes::GK_F18;
  case KEYCODES::KEY_F19:
    return ul::KeyCodes::GK_F19;
  case KEYCODES::KEY_F20:
    return ul::KeyCodes::GK_F20;
  case KEYCODES::KEY_F21:
    return ul::KeyCodes::GK_F21;
  case KEYCODES::KEY_F22:
    return ul::KeyCodes::GK_F22;
  case KEYCODES::KEY_F23:
    return ul::KeyCodes::GK_F23;
  case KEYCODES::KEY_F24:
    return ul::KeyCodes::GK_F24;
  case KEYCODES::KEY_F25:
    return ul::KeyCodes::GK_UNKNOWN;
  case KEYCODES::KEY_KP_0:
    return ul::KeyCodes::GK_NUMPAD0;
  case KEYCODES::KEY_KP_1:
    return ul::KeyCodes::GK_NUMPAD1;
  case KEYCODES::KEY_KP_2:
    return ul::KeyCodes::GK_NUMPAD2;
  case KEYCODES::KEY_KP_3:
    return ul::KeyCodes::GK_NUMPAD3;
  case KEYCODES::KEY_KP_4:
    return ul::KeyCodes::GK_NUMPAD4;
  case KEYCODES::KEY_KP_5:
    return ul::KeyCodes::GK_NUMPAD5;
  case KEYCODES::KEY_KP_6:
    return ul::KeyCodes::GK_NUMPAD6;
  case KEYCODES::KEY_KP_7:
    return ul::KeyCodes::GK_NUMPAD7;
  case KEYCODES::KEY_KP_8:
    return ul::KeyCodes::GK_NUMPAD8;
  case KEYCODES::KEY_KP_9:
    return ul::KeyCodes::GK_NUMPAD9;
  case KEYCODES::KEY_KP_DECIMAL:
    return ul::KeyCodes::GK_DECIMAL;
  case KEYCODES::KEY_KP_DIVIDE:
    return ul::KeyCodes::GK_DIVIDE;
  case KEYCODES::KEY_KP_MULTIPLY:
    return ul::KeyCodes::GK_MULTIPLY;
  case KEYCODES::KEY_KP_SUBTRACT:
    return ul::KeyCodes::GK_SUBTRACT;
  case KEYCODES::KEY_KP_ADD:
    return ul::KeyCodes::GK_ADD;
  case KEYCODES::KEY_KP_ENTER:
    return ul::KeyCodes::GK_RETURN;
  case KEYCODES::KEY_KP_EQUAL:
    return ul::KeyCodes::GK_OEM_PLUS;
  case KEYCODES::KEY_LEFT_SHIFT:
    return ul::KeyCodes::GK_SHIFT;
  case KEYCODES::KEY_LEFT_CONTROL:
    return ul::KeyCodes::GK_CONTROL;
  case KEYCODES::KEY_LEFT_ALT:
    return ul::KeyCodes::GK_MENU;
  case KEYCODES::KEY_LEFT_SUPER:
    return ul::KeyCodes::GK_LWIN;
  case KEYCODES::KEY_RIGHT_SHIFT:
    return ul::KeyCodes::GK_SHIFT;
  case KEYCODES::KEY_RIGHT_CONTROL:
    return ul::KeyCodes::GK_CONTROL;
  case KEYCODES::KEY_RIGHT_ALT:
    return ul::KeyCodes::GK_MENU;
  case KEYCODES::KEY_RIGHT_SUPER:
    return ul::KeyCodes::GK_RWIN;
  case KEYCODES::KEY_MENU:
    return ul::KeyCodes::GK_UNKNOWN;
  default:
    return ul::KeyCodes::GK_UNKNOWN;
  }
}

ul::MouseEvent::Button Ultralight::keycodeToUltralightButtonCode(KEYCODES key) {
  switch (key) {
  case KEYCODES::MOUSE_BUTTON_LEFT:
    return ul::MouseEvent::kButton_Left;
  case KEYCODES::MOUSE_BUTTON_MIDDLE:
    return ul::MouseEvent::kButton_Middle;
  case KEYCODES::MOUSE_BUTTON_RIGHT:
    return ul::MouseEvent::kButton_Right;
  default:
    return ul::MouseEvent::kButton_None;
  }
}

}; // namespace wind
