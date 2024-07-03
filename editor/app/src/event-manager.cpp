#include "utils/includes.h"

#include <JavaScriptCore/JSRetainPtr.h>
#include <editor/event-manager.hpp>
#include <editor/generated/ui.hpp>
#include <editor/js-core-utils.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <utils/utils.h>

namespace editor {
using json = nlohmann::json;

JSValueRef handleCppEvent(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount,
  const JSValueRef arguments[], JSValueRef* exception) {

  std::string eventJson = JSValueToStdString(ctx, arguments[0]);

  auto json = nlohmann::json::parse(eventJson);

  JSEvent event = jsonToEvent(json);
  // from_json(json, event);

  // CppEvents::SaveProject::Input input;
  // from_json(json['data'], input);

  auto temp = new CppEvents::Methods();

  std::unordered_map<std::string, std::function<void()>> handlers = {
    {"saveProject", [&]() {
       temp->saveProject(CppEvents::SaveProject::Input{event.data['name'], event.data['createdAt'], event.data['maps']})
     }}};

  auto it = handlers.find(event.name);

  if (it != handlers.end()) {
    it->second();
  }

  // const char* str =
  //   "console.log('BIMBO')";

  // JSStringRef script = JSStringCreateWithUTF8CString(str);

  // JSEvaluateScript(ctx, script, 0, 0, 0, 0);

  // JSStringRelease(script);

  return JSValueMakeNull(ctx);
}

JSValueRef emitJSEvent(JSContextRef context, JSEvent event, JSValueRef* exception) {
  JSObjectRef globalObject = JSContextGetGlobalObject(context);

  JSStringRef eventJson = JSStringCreateWithUTF8CString(event.toJson().dump().c_str());

  JSValueRef args[1];
  args[0] = JSValueMakeString(context, eventJson);
  size_t argsLength = sizeof(args) / sizeof(JSValueRef*);

  JSObjectRef windowObject = getJSObject(context, globalObject, "window");

  JSObjectRef emitter = getJSObject(context, windowObject, "emitJSEvent");

  JSValueRef result = JSObjectCallAsFunction(context, emitter, nullptr, argsLength, args, exception);

  return result;
}

} // namespace editor
