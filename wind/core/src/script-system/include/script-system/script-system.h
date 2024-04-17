#pragma once

#include "declaration.h"
#include "error.h"
#include "hostfxr.h"
#include "utils/utils.h"
#include <chrono>
#include <spdlog/spdlog.h>
#include <string.h>
#include <tuple>

namespace wind {

class ScriptSystem {
  friend class ScriptSystemHostfxr;

public:
  template <typename... FunctionArgs>
  int run(std::string dotnetType, std::string methodName, FunctionArgs... args) {
    load_assembly_and_get_function_pointer_fn functionPointer = nullptr;
    functionPointer = getFunctionPointerFromAssembly();
    verify<ScriptSystemError>(functionPointer != nullptr);

    component_entry_point_fn function = nullptr;

#ifdef _WIN32
    int rc = functionPointer(
      stringToWindowsString(dllPath.string()).c_str(),
      stringToWindowsString(dotnetType).c_str(),
      stringToWindowsString(methodName).c_str(),
      nullptr,
      nullptr,
      (void**)&function);
#else
    int rc = functionPointer(
      dllPath.c_str(),
      dotnetType.c_str(),
      methodName.c_str(),
      nullptr,
      nullptr,
      (void**)&function);
#endif

    verify<ScriptSystemError>(rc == 0 && function != nullptr);

    // Adjust for proper alignment by adding the size of a void pointer,
    // and round up to the nearest multiple of the size of a void pointer.
    size_t bufferSize = ((sizeof(args) + ...) + sizeof(void*) - 1) / sizeof(void*) * sizeof(void*);

    unsigned char* buffer = new unsigned char[bufferSize];

    size_t offset = 0;
    ((std::memcpy(buffer + offset, &args, sizeof(args)), offset += sizeof(args)), ...);

    function(buffer, bufferSize);

    delete[] buffer;

    return EXIT_SUCCESS;
  };

  ScriptSystem(const fs::path& rootPath, const fs::path& dllPath, ScriptSystemHostfxr hostfxr);

private:
  ScriptSystemHostfxr hostfxr;
  fs::path rootPath;
  fs::path dllPath;

  load_assembly_and_get_function_pointer_fn getFunctionPointerFromAssembly();

  ~ScriptSystem();
};

} // namespace wind
