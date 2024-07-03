#include <editor/event-manager.hpp>
#include <editor/generated/ui.hpp>
#include <editor/js-core-utils.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace JsEvents {

LoadProject::Output Methods::loadProject(const LoadProject::Input& input, JSContextRef context) {
  JSValueRef exception = nullptr;

  editor::JSEvent event;
  event.name = "loadProject";
  event.add("createdAt", input.createdAt);
  event.add("maps", input.maps);
  event.add("name", input.name);

  editor::emitJSEvent(input, event, exception);

  return LoadProject::Output{true};
};
} // namespace JsEvents

namespace CppEvents {
SaveProject::Output Methods::saveProject(const SaveProject::Input& input) {
  return SaveProject::Output{true};
};
} // namespace CppEvents
