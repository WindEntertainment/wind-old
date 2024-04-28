#pragma once

#include "declaration.h"
#include "utils/utils.h"
#include <string.h>

#ifdef _WIN32

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

  void init(const fs::path& configPath);
  hostfxr_handle getConfig();
  ScriptSystem* createScriptSystem(const fs::path& rootPath, const fs::path& dllPath);
  void stop();

private:
  fs::path configPath;
  hostfxr_initialize_for_dotnet_command_line_fn fptrInitCmd;
  hostfxr_initialize_for_runtime_config_fn fptrInitConfig;
  hostfxr_handle context = nullptr;
  hostfxr_close_fn fptrClose;

  void loadPointers();
  void initConfig();
  void* loadLibrary(const char_t* path);
  void* getExport(void* h, const char* name);
};
} // namespace wind
