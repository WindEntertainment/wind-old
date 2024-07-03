#include <JavaScriptCore/JSRetainPtr.h>
#include <boost/hana.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <wind-ultralight/js-core-utils.hpp>

namespace wind {

namespace pt = boost::property_tree;
namespace hana = boost::hana;

JSValueRef emitJSEvent(JSContextRef context, const char* event, JSValueRef* exception) {
  JSObjectRef globalObject = JSContextGetGlobalObject(context);

  JSStringRef eventJson = JSStringCreateWithUTF8CString(event);

  JSValueRef args[1];
  args[0] = JSValueMakeString(context, eventJson);
  size_t argsLength = sizeof(args) / sizeof(JSValueRef*);

  JSObjectRef windowObject = getJSObject(context, globalObject, "window");

  JSObjectRef emitter = getJSObject(context, windowObject, "emitJSEvent");

  JSValueRef result = JSObjectCallAsFunction(context, emitter, nullptr, argsLength, args, exception);

  return result;
}

} // namespace wind
