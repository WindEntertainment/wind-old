#include <boost/hana.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <editor/event-manager.hpp>
#include <editor/generated/ui.hpp>
#include <wind-event-manager/convertor.hpp>
#include <wind-event-manager/emitter.hpp>

namespace JsEvents {

namespace pt = boost::property_tree;
namespace hana = boost::hana;

LoadProject::Output Methods::loadProject(const LoadProject::Input& input, JSContextRef context) {
  JSValueRef exception = nullptr;

  const char* event = wind::structToJsonObjectWithName<LoadProject::Input>("loadProject", input);

  JSValueRef result = wind::emitJSEvent(context, event, &exception);

  return LoadProject::Output{exception ? false : true};
};
} // namespace JsEvents

namespace CppEvents {
SaveProject::Output Methods::saveProject(const SaveProject::Input& input, JSContextRef context) {
  spdlog::info("Data: {}, {}", input.name, input.createdAt);
  return SaveProject::Output{true};
};
} // namespace CppEvents
