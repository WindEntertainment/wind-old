#pragma once

#include "declaration.h"
#include "utils/utils.h"
#include <string.h>

#ifdef WINDOWS
#include <Windows.h>

#else

#include <dlfcn.h>
#include <limits.h>

#define MAX_PATH PATH_MAX

#endif

namespace wind {
class ScriptSystemHostfxr {
public:
  std::list<ScriptSystem*> scriptSystems;
  hostfxr_get_runtime_delegate_fn fptrGetDelegate;

  void init(std::string configPath);
  hostfxr_handle getConfig();
  ScriptSystem* createScriptSystem(std::string rootPath, std::string dllPath);
  void stop();

private:
  std::string configPath;
  hostfxr_initialize_for_dotnet_command_line_fn fptrInitCmd;
  hostfxr_initialize_for_runtime_config_fn fptrInitConfig;
  hostfxr_handle context = nullptr;
  hostfxr_close_fn fptrClose;

  void loadPointers();
  void initConfig();
  void* loadLibrary(const std::string path);
  void* getExport(void* h, const char* name);
};
} // namespace wind
