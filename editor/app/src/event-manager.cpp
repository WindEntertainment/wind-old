#include "utils/includes.h"

#include <JavaScriptCore/JSRetainPtr.h>
#include <boost/hana.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <editor/event-manager.hpp>
#include <editor/generated/ui.hpp>
#include <spdlog/spdlog.h>
#include <utils/utils.h>
#include <wind-event-manager/convertor.hpp>
#include <wind-ultralight/js-core-utils.hpp>

namespace editor {
namespace pt = boost::property_tree;
namespace hana = boost::hana;

JSValueRef handleCppEvent(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount,
  const JSValueRef arguments[], JSValueRef* exception) {

  std::string eventJson = wind::JSValueToStdString(ctx, arguments[0]);

  pt::ptree tree;
  std::istringstream ss(eventJson);
  pt::read_json(ss, tree);

  std::string name = tree.get<std::string>("name");
  std::string data = tree.get<std::string>("data");

  auto temp = new CppEvents::Methods();

  std::unordered_map<std::string, std::function<void()>> handlers = {
    {"saveProject", [&]() {
       temp->saveProject(wind::jsonToStruct<CppEvents::SaveProject::Input>(data), ctx);
     }}};

  auto it = handlers.find(name);

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

} // namespace editor
