#include "editor/generated/ui.hpp"

namespace JsEvents {
using namespace LoadProject;
using namespace wind;
using namespace editor;
LoadProject::Output Methods::loadProject(const LoadProject::Input& input, JSContextRef context) {
  JSValueRef exception = nullptr;

  const char* event = wind::structToJsonObjectWithName<LoadProject::Input>("loadProject", input);

  JSValueRef result = wind::emitJSEvent(context, event, &exception);

  return LoadProject::Output{exception ? false : true};
};
} // namespace JsEvents

namespace CppEvents {
using namespace SaveProject;
using namespace wind;
using namespace editor;
SaveProject::Output Methods::saveProject(const SaveProject::Input& input, JSContextRef context) {
  spdlog::info("Data: {}, {}", input.name, input.createdAt);
  return SaveProject::Output{true};
};
} // namespace CppEvents
