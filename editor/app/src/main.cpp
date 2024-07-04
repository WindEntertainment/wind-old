#include "editor/utils.hpp" // IWYU pragma: export
#include <glad/glad.h>

#include "input-system/context.h"
#include "input-system/keys.h"

#include "editor/event-manager.hpp"
#include "utils/includes.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <algorithm>
#include <asset-manager/asset-manager.hpp>
#include <editor/generated/ui.hpp>
#include <functional>
#include <input-system/input-system.h>
#include <iostream>
#include <ostream>
#include <renderer/renderer.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <tuple>
#include <utils/includes.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

int main(int argc, char** argv) {

#ifndef NDEBUG
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("----Debug configuration!----");
#endif

  using namespace wind;
  using namespace editor;
  using namespace wind::assets;

  // v1

  // extern char** environ;

  // // Iterate through each environment variable
  // for (char** env = environ; *env != nullptr; ++env) {
  //   // Split each environment variable into name and value
  //   std::string envVar(*env);
  //   size_t equalSignPos = envVar.find('=');
  //   std::string name = envVar.substr(0, equalSignPos);
  //   std::string value = envVar.substr(equalSignPos + 1);

  //   // Print the name and value of the environment variable
  //   std::cout << "Environment variable: " << name << "=" << value << std::endl;
  // }

  // v2

  // const char* exampleVar = std::getenv("DOTNET_ROOT");
  // if (exampleVar != nullptr) {
  //   // Use the value of the environment variable
  //   std::cout << "Environment variable EXAMPLE_VAR: " << exampleVar << std::endl;
  // } else {
  //   // Handle the case where the environment variable does not exist
  //   std::cerr << "Environment variable EXAMPLE_VAR not found." << std::endl;
  // }

  //=========Configure path===============//

  fs::path root = fs::path(argv[0]).parent_path();
  fs::current_path(root);

  //=========Assets Pipeline===============//

  AssetManager::loadBundle("res/Ultralight.bundle");
  AssetManager::loadBundle("res/Main.bundle");

  // auto image = AssetManager::getAsset<unsigned char>("main/art/test.png");

  //=========Input System==================//

  InputSystem::createTriggersFromFile("main/configs/triggers.yml");
  InputSystem::createTriggersFromFile("resources/triggers.yml");
  InputSystem::addTriggerCallbacks("ultralightMouseMove", new std::function(Ultralight::triggerMoveEvent));
  InputSystem::addTriggerCallbacks("ultralightMouseScroll", new std::function(Ultralight::triggerScrollEvent));
  InputSystem::addTriggerCallbacks("ultralightMousePress", new std::function(Ultralight::triggerMousePressEvent));
  InputSystem::addTriggerCallbacks("ultralightMouseRelease", new std::function(Ultralight::triggerMouseReleaseEvent));
  InputSystem::addTriggerCallbacks("ultralightKeyPress", new std::function(Ultralight::triggerKeyPressEvent));
  InputSystem::addTriggerCallbacks("ultralightKeyHold", new std::function(Ultralight::triggerKeyHoldEvent));
  InputSystem::addTriggerCallbacks("ultralightKeyRelease", new std::function(Ultralight::triggerKeyReleaseEvent));
  InputSystem::addTriggerCallbacks("ultralightChars", new std::function(Ultralight::triggerCharEvent));

  //===============Window==================//

  Window::init([](Window::Config* self) {
    self->title = "Dreich";
    self->fullScreen = false;
    self->size = {800, 600};
    self->vSync = true;
  });

  //=============Ultralight================//

  Ultralight::init();

  std::function<void(ultralight::View*)> onDomReady = [](ul::View* view) {
    auto scoped_context = view->LockJSContext();

    JSContextRef ctx = (*scoped_context);

    JSStringRef name = JSStringCreateWithUTF8CString("emitCppEvent");

    JSObjectRef func = JSObjectMakeFunctionWithCallback(ctx, name, handleCppEvent);

    JSObjectRef globalObj = JSContextGetGlobalObject(ctx);

    JSObjectSetProperty(ctx, globalObj, name, func, 0, 0);

    JSStringRelease(name);
  };

  auto viewLogger = new wind::ViewLogger();
  auto loadLogger = new wind::LoadLogger(onDomReady);
  auto networkLogger = new wind::NetworkLogger();

  const auto uiTexture = Ultralight::loadView("main/UI/dist/index.html", {800, 600}, viewLogger, loadLogger, networkLogger);

  auto onClick = [](InputSystemContext* inputSystemContext) {
    forEach(Ultralight::m_views, [&](auto view) {
      auto scoped_context = view->LockJSContext();
      JSContextRef context = (*scoped_context);

      int date = 1719923;
      auto emitter = new JsEvents::Methods();

      emitter->loadProject(JsEvents::LoadProject::Input{"Project1", date, "Map1,Map2"}, context);
    });
  };

  // auto addCppEventToJSScope = [](InputSystemContext* inputSystemContext) {
  //   forEach(Ultralight::m_views, [&](auto view) {
  //     auto scoped_context = view->LockJSContext();

  //     JSContextRef ctx = (*scoped_context);

  //     JSStringRef name = JSStringCreateWithUTF8CString("emitCppEvent");

  //     JSObjectRef func = JSObjectMakeFunctionWithCallback(ctx, name, handleCppEvent);

  //     JSObjectRef globalObj = JSContextGetGlobalObject(ctx);

  //     JSObjectSetProperty(ctx, globalObj, name, func, 0, 0);

  //     JSStringRelease(name);
  //   });
  // };

  InputSystem::addTriggerCallbacks("ultralightMousePress", new std::function(onClick));

  //=============Main loop=================//

  while (Window::update()) {
    Renderer::clear({1.f, 0.f, 0.f, 1});

    Ultralight::update();

    Ultralight::render();

    Renderer::drawTexture(uiTexture, {1, 1}, {0, 0, 0}, {0, 0, 0}, {800, 600});

    Window::show();
  }

  return EXIT_SUCCESS;
};
