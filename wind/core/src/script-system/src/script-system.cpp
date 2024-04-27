
#include <chrono>
#include <string.h>

#include "script-system/error.h"
#include "script-system/hostfxr.h"
#include "script-system/script-system.h"
#include "utils/utils.h"

namespace wind {
load_assembly_and_get_function_pointer_fn ScriptSystem::getFunctionPointerFromAssembly() {
  auto context = hostfxr.getConfig();

  void* functionPointer = nullptr;

  int rc = hostfxr.fptrGetDelegate(
    context,
    hdt_load_assembly_and_get_function_pointer,
    &functionPointer);

  verify(ScriptSystemError, rc == 0 && functionPointer != nullptr);
  return (load_assembly_and_get_function_pointer_fn)functionPointer;
}

ScriptSystem::ScriptSystem(const fs::path& rootPath, const fs::path& dllPath, ScriptSystemHostfxr hostfxr) {
  this->rootPath = rootPath;
  this->dllPath = dllPath;
  this->hostfxr = hostfxr;
};

ScriptSystem::~ScriptSystem(){};
} // namespace wind
