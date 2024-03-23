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
    int rc = functionPointer(
      dllPath.c_str(),
      dotnetType.c_str(),
      methodName.c_str(),
      nullptr,
      nullptr,
      (void**)&function);

    verify<ScriptSystemError>(rc == 0 && function != nullptr);

    std::tuple<FunctionArgs...>
      argsTuple = std::make_tuple(args...);

    function(&argsTuple, sizeof(argsTuple));

    return EXIT_SUCCESS;
  };

  ScriptSystem(std::string rootPath, std::string dllPath, ScriptSystemHostfxr hostfxr);

private:
  ScriptSystemHostfxr hostfxr;
  std::string rootPath;
  std::string dllPath;

  load_assembly_and_get_function_pointer_fn getFunctionPointerFromAssembly();

  template <typename... Args>
  std::tuple<Args...>* getArgsPointer(Args... args) {
    return new std::tuple<Args...>(args...);
  }

  ~ScriptSystem();
};

} // namespace wind
