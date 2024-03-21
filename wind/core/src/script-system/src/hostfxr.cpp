

#include "script-system/hostfxr.h"
#include "script-system/script-system.h"
#include "utils/utils.h"
#include <algorithm>
#ifdef WINDOWS
#include <Windows.h>

#else

#include <dlfcn.h>
#include <limits.h>

#define MAX_PATH PATH_MAX

#endif

namespace wind {

bool ScriptSystemHostfxr::loadPointers() {
  if (fptrInitConfig && fptrGetDelegate && fptrClose)
    return true;

  get_hostfxr_parameters params{sizeof(get_hostfxr_parameters), nullptr, nullptr};

  char_t buffer[MAX_PATH];
  size_t buffer_size = sizeof(buffer) / sizeof(char_t);

  int rc = get_hostfxr_path(buffer, &buffer_size, &params);
  if (rc != 0)
    return false;

  void* lib = loadLibrary(buffer);
  fptrInitCmd = (hostfxr_initialize_for_dotnet_command_line_fn)getExport(lib, "hostfxr_initialize_for_dotnet_command_line");
  fptrInitConfig = (hostfxr_initialize_for_runtime_config_fn)getExport(lib, "hostfxr_initialize_for_runtime_config");
  fptrGetDelegate = (hostfxr_get_runtime_delegate_fn)getExport(lib, "hostfxr_get_runtime_delegate");
  fptrClose = (hostfxr_close_fn)getExport(lib, "hostfxr_close");

  return (fptrInitConfig && fptrGetDelegate && fptrClose);
}

bool ScriptSystemHostfxr::initConfig() {
  if (context)
    return true;

  int rc = fptrInitConfig(configPath.c_str(), nullptr, &context);

  if (rc != 0 || context == nullptr) {
    std::cerr << "Init failed: " << std::hex << std::showbase << rc << std::endl;
    fptrClose(context);
    return false;
  }

  return true;
}

hostfxr_handle ScriptSystemHostfxr::getConfig() {
  return context;
}

bool ScriptSystemHostfxr::init(std::string configPath) {
  this->configPath = configPath;

  return loadPointers() && initConfig();
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

void* ScriptSystemHostfxr::loadLibrary(const std::string path) {
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

void* ScriptSystemHostfxr::getExport(void* h, const char* name) {
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
} // namespace wind
