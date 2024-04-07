#include "script-system/hostfxr.h"
#include "script-system/error.h"
#include "script-system/script-system.h"
#include "utils/utils.h"
#include <algorithm>

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#include <limits.h>
#define MAX_PATH PATH_MAX
#endif

namespace wind {

void ScriptSystemHostfxr::loadPointers() {
  if (fptrInitConfig && fptrGetDelegate && fptrClose)
    return;

  get_hostfxr_parameters params{sizeof(get_hostfxr_parameters), nullptr, nullptr};

  char_t buffer[MAX_PATH];
  size_t buffer_size = sizeof(buffer) / sizeof(char_t);

  int rc = get_hostfxr_path(buffer, &buffer_size, &params);

  verify<ScriptSystemError>(rc == 0);

  void* lib = loadLibrary(buffer);
  fptrInitCmd = (hostfxr_initialize_for_dotnet_command_line_fn)getExport(lib, "hostfxr_initialize_for_dotnet_command_line");
  fptrInitConfig = (hostfxr_initialize_for_runtime_config_fn)getExport(lib, "hostfxr_initialize_for_runtime_config");
  fptrGetDelegate = (hostfxr_get_runtime_delegate_fn)getExport(lib, "hostfxr_get_runtime_delegate");
  fptrClose = (hostfxr_close_fn)getExport(lib, "hostfxr_close");

  verify<ScriptSystemError>(fptrInitConfig && fptrGetDelegate && fptrClose);
}

void ScriptSystemHostfxr::initConfig() {
  if (context)
    return;

#ifdef _WIN32
  int rc = fptrInitConfig(stringToWindowsString(configPath), nullptr, &context);
#else
  int rc = fptrInitConfig(configPath.c_str(), nullptr, &context);
#endif

  if (rc != 0 || context == nullptr) {
    std::stringstream ss;
    ss << std::hex << std::showbase << rc;
    spdlog::debug("Init failed: {}", ss.str());

    fptrClose(context);
    // throw new ScriptSystemError();
  }
}

hostfxr_handle ScriptSystemHostfxr::getConfig() {
  return context;
}

void ScriptSystemHostfxr::init(std::string configPath) {
  this->configPath = configPath;
  loadPointers();
  initConfig();
}

void ScriptSystemHostfxr::stop() {
  std::for_each(scriptSystems.begin(), scriptSystems.end(), [](auto scriptSystem) {
    delete scriptSystem;
  });

  fptrClose(context);
}

ScriptSystem* ScriptSystemHostfxr::createScriptSystem(std::string rootPath, std::string dllPath) {
  auto scriptSystem = new ScriptSystem(rootPath, dllPath, *this);
  scriptSystems.push_back(scriptSystem);
  return scriptSystem;
}

void* ScriptSystemHostfxr::loadLibrary(const char_t* path) {
#ifdef _WIN32
  HMODULE h = ::LoadLibraryW(path);
#else
  void* h = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
#endif

  verify<ScriptSystemError>(h != nullptr);
  return (void*)h;
};

void* ScriptSystemHostfxr::getExport(void* h, const char* name) {
#ifdef _WIN32
  void* f = ::GetProcAddress((HMODULE)h, name);
#else
  void* f = dlsym(h, name);
#endif

  verify<ScriptSystemError>(f != nullptr);
  return f;
};
} // namespace wind
