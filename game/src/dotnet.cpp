
#include <assert.h>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>
#include <vector>

#include "inc.vs/nethost.h"

#include "inc/coreclr_delegates.h"
#include "inc/hostfxr.h"
#include "utils/utils.h"

#ifdef WINDOWS
#include <Windows.h>

#else

#include <dlfcn.h>
#include <limits.h>

#define MAX_PATH PATH_MAX

#endif

class ScriptSystem {
public:
  bool isInitialized;
  std::string rootPath;
  std::string dllPath;
  std::string configPath;
  hostfxr_initialize_for_dotnet_command_line_fn fptrInitCmd;
  hostfxr_initialize_for_runtime_config_fn fptrInitConfig;
  hostfxr_get_runtime_delegate_fn fptrGetDelegate;
  hostfxr_handle context = nullptr;
  hostfxr_close_fn fptrClose;

  bool loadHostfxr() {
    get_hostfxr_parameters params{sizeof(get_hostfxr_parameters), nullptr, nullptr};
    // Pre-allocate a large buffer for the path to hostfxr
    char_t buffer[MAX_PATH];
    size_t buffer_size = sizeof(buffer) / sizeof(char_t);

    int rc = get_hostfxr_path(buffer, &buffer_size, &params);
    if (rc != 0)
      return false;

    // Load hostfxr and get desired exports
    void* lib = loadLibrary(buffer);
    fptrInitCmd = (hostfxr_initialize_for_dotnet_command_line_fn)getExport(lib, "hostfxr_initialize_for_dotnet_command_line");
    fptrInitConfig = (hostfxr_initialize_for_runtime_config_fn)getExport(lib, "hostfxr_initialize_for_runtime_config");
    fptrGetDelegate = (hostfxr_get_runtime_delegate_fn)getExport(lib, "hostfxr_get_runtime_delegate");
    fptrClose = (hostfxr_close_fn)getExport(lib, "hostfxr_close");
    isInitialized = fptrInitConfig && fptrGetDelegate && fptrClose;

    return (fptrInitConfig && fptrGetDelegate && fptrClose);
  }

  load_assembly_and_get_function_pointer_fn getFunctionPointerFromAssembly() {
    if (!context) {
      int rc = fptrInitConfig(configPath.c_str(), nullptr, &context);
      if (rc != 0 || context == nullptr) {
        std::cerr << "Init failed: " << std::hex << std::showbase << rc << std::endl;
        fptrClose(context);
        return nullptr;
      }
    }

    void* functionPointer = nullptr;

    int rc = fptrGetDelegate(
        context,
        hdt_load_assembly_and_get_function_pointer,
        &functionPointer);

    if (rc != 0 || functionPointer == nullptr)
      std::cerr << "Get delegate failed: " << std::hex << std::showbase << rc << std::endl;

    return (load_assembly_and_get_function_pointer_fn)functionPointer;
  }

  void init(std::string rootPath, std::string dllPath, std::string configPath) {
    this->rootPath = rootPath;
    this->dllPath = dllPath;
    this->configPath = configPath;
    if (!isInitialized && !loadHostfxr()) {
      assert(false && "Failure: load_hostfxr()");
    }
  }

  void stop() {
    fptrClose(context);
  }

  int run(std::string dotnetType, std::string methodName, auto args) {
    load_assembly_and_get_function_pointer_fn functionPointer = nullptr;
    functionPointer = getFunctionPointerFromAssembly();
    assert(functionPointer != nullptr && "Failure: get_dotnet_load_assembly()");

    component_entry_point_fn function = nullptr;
    int rc = functionPointer(
        dllPath.c_str(),
        dotnetType.c_str(),
        methodName.c_str(),
        nullptr,
        nullptr,
        (void**)&function);

    assert(rc == 0 && function != nullptr && "Failure: load_assembly_and_get_function_pointer()");

    function(&args, sizeof(args));

    return EXIT_SUCCESS;
  }

  void* loadLibrary(const std::string path) {
#ifdef WINDOWS
    HMODULE h = ::LoadLibraryW(path);
    assert(h != nullptr);
    return (void*)h;
#else
    void* h = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
    assert(h != nullptr);
    return h;
#endif
  };

  void* getExport(void* h, const char* name) {
#ifdef WINDOWS
    void* f = ::GetProcAddress((HMODULE)h, name);
    assert(f != nullptr);
    return f;
#else
    void* f = dlsym(h, name);
    assert(f != nullptr);
    return f;
#endif
  };
};

int main(int argc, char* argv[]) {
  auto scriptSystem = new ScriptSystem();

  auto hostPath = fs::absolute(argv[0]).parent_path() / "assets/scripts/bin/Release/";

  scriptSystem->init(hostPath, hostPath / "Scripts.dll", hostPath / "Scripts.runtimeconfig.json");

  struct FunctionsArgs {
    const char_t* message;
    int number;
  };

  FunctionsArgs args{"from host!", 1};

  scriptSystem->run("Scripts.Lib2, Scripts", "Hello", args);
  scriptSystem->run("Scripts.Lib2, Scripts", "Hello", args);
  scriptSystem->run("Scripts.Lib2, Scripts", "HelloAgain", args);

  scriptSystem->stop();

  return 0;
  // }
}
