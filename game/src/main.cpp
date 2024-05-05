#include <glad/glad.h>

#include "game/generated/ui.hpp"
#include "input-system/context.h"
#include "input-system/keys.h"
#include "script-system/hostfxr.h"
#include "script-system/script-system.h"

#include "utils/includes.h"

#include <algorithm>
#include <asset-manager/asset-manager.hpp>
#include <functional>
#include <input-system/input-system.h>
#include <ostream>
#include <renderer/particle.h>
#include <renderer/renderer.h>
#include <spdlog/spdlog.h>
#include <utils/includes.h>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

#include <JavaScriptCore/JSRetainPtr.h>

std::string JSValueRefToString(JSContextRef context, JSValueRef value) {
  // Convert JSValueRef to JSStringRef
  JSStringRef jsStringRef = JSValueToStringCopy(context, value, NULL);

  // Get the length of the string
  size_t length = JSStringGetMaximumUTF8CStringSize(jsStringRef);

  // Allocate a buffer for the UTF-8 string
  char* utf8Buffer = new char[length];

  // Convert JSStringRef to UTF-8 C string
  JSStringGetUTF8CString(jsStringRef, utf8Buffer, length);

  // Create std::string from the UTF-8 C string
  std::string result(utf8Buffer);

  // Clean up memory
  delete[] utf8Buffer;
  JSStringRelease(jsStringRef);

  return result;
}

int main(int argc, char** argv) {

#ifndef NDEBUG
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("----Debug configuration!----");
#endif

  using namespace wind;
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

  auto image = AssetManager::getAsset<unsigned char>("main/art/test.png");

  //=========Input System==================//

  InputSystem::createTriggersFromFile("main/configs/triggers.yml");
  InputSystem::addTriggerCallbacks("ultralightMouseMove", &Ultralight::triggerMoveEvent);
  InputSystem::addTriggerCallbacks("ultralightMouseScroll", &Ultralight::triggerScrollEvent);
  InputSystem::addTriggerCallbacks("ultralightMousePress", &Ultralight::triggerMousePressEvent);
  InputSystem::addTriggerCallbacks("ultralightMouseRelease", &Ultralight::triggerMouseReleaseEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyPress", &Ultralight::triggerKeyPressEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyHold", &Ultralight::triggerKeyHoldEvent);
  InputSystem::addTriggerCallbacks("ultralightKeyRelease", &Ultralight::triggerKeyReleaseEvent);
  InputSystem::addTriggerCallbacks("ultralightChars", &Ultralight::triggerCharEvent);

  //===============Window==================//

  Window::init([](Window::Config* self) {
    self->title = "Dreich";
    self->fullScreen = false;
    self->size = {800, 600};
    self->vSync = true;
  });

  //=============Ultralight================//

  Ultralight::init();

  const auto uiTexture = Ultralight::loadView("main/UI/dist/index.html", {800, 600});

  auto piska = [](InputSystemContext* context) {
    std::ifstream input("/Users/stasangoliuk/Desktop/dreich/editor/project1/state.json", std::ios_base::binary);

    std::string fileContent;
    {
      std::stringstream buffer;
      buffer << input.rdbuf();
      fileContent = buffer.str();
    }

    forEach(Ultralight::m_views, [&](auto view) {
      auto scoped_context = view->LockJSContext();

      // Typecast to the underlying JSContextRef.

      JSContextRef ctx = (*scoped_context);

      std::string m = fmt::format("{}", fileContent);

      const char* message = m.c_str();
      // spdlog::info(message);
      // Get the ShowMessage function by evaluating a script. We could have
      // also used JSContextGetGlobalObject() and JSObjectGetProperty() to
      // retrieve this from the global window object as well.
      // Create our string of JavaScript, automatically managed by JSRetainPtr
      JSRetainPtr<JSStringRef>
        str = adopt(
          JSStringCreateWithUTF8CString("openAsset"));

      // Evaluate the string "ShowMessage"
      JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

      // Check if 'func' is actually an Object and not null
      if (JSValueIsObject(ctx, func)) {

        // Cast 'func' to an Object, will return null if typecast failed.
        JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

        // Check if 'funcObj' is a Function and not null

        if (funcObj && JSObjectIsFunction(ctx, funcObj)) {

          // Create a JS string from null-terminated UTF8 C-string, store it
          // in a smart pointer to release it when it goes out of scope.
          JSRetainPtr<JSStringRef> msg =
            adopt(JSStringCreateWithUTF8CString(message));

          // Create our list of arguments (we only have one)
          const JSValueRef args[] = {JSValueMakeString(ctx, msg.get())};

          // Count the number of arguments in the array.
          size_t num_args = sizeof(args) / sizeof(JSValueRef*);

          // Create a place to store an exception, if any
          JSValueRef exception = 0;
          // Call the ShowMessage() function with our list of arguments.
          JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0, num_args, args, &exception);
          //  spdlog::info(message);
          if (exception) {
            spdlog::info(JSValueRefToString(ctx, exception));
            // Handle any exceptions thrown from function here.
          }
          if (result) {
            spdlog::info(JSValueRefToString(ctx, result));
            // Handle result (if any) here.
          }
        }
      }
    });
  };

  // InputSystem::addTriggerCallbacks("ultralightMousePress", piska);

  // void MyApp::OnDOMReady(ul::View * caller,
  //   uint64_t frame_id,
  //   bool is_main_frame,
  //   const ul::String& url) {
  //   caller->EvaluateScript("ShowMessage('Howdy!')");
  // }

  //============Script System==============//

  // auto scriptsPath = fs::path("./res/Managed/");
  // auto hostfxr = new ScriptSystemHostfxr();

  // hostfxr->init(scriptsPath / "Scripts.runtimeconfig.json");

  // ScriptSystem* scriptSystem = hostfxr->createScriptSystem(scriptsPath, scriptsPath / "Scripts.dll");

  // scriptSystem->run("Scripts.Lib, Scripts", "HelloAgain", "from host!", 1);
  // scriptSystem->run("Scripts.Lib, Scripts", "Hello", "from host!", 1);

  //=============Main loop=================//

  while (Window::update()) {
    Renderer::clear({1.f, 0.f, 0.f, 1});

    Ultralight::update();

    Ultralight::render();

    Renderer::drawTexture(uiTexture, {1, 1}, {0, 0, 0}, {0, 0, 0}, {800, 600, 1});

    Window::show();
  }

  // hostfxr->stop();

  return EXIT_SUCCESS;
}
