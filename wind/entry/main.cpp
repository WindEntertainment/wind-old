#include <script-system/script-system.h>

int main(int argc, char** argv) {
#ifndef NDEBUG
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("----Debug configuration!----");
#endif

  using namespace wind;

  auto dotnetPath = fs::path("./res/Managed/");

  try {
    auto hostfxr = new ScriptSystemHostfxr();

    hostfxr->init(dotnetPath / "Game.runtimeconfig.json");
    ScriptSystem* scriptSystem = hostfxr->createScriptSystem(dotnetPath, dotnetPath / "Game.dll");

    scriptSystem->run("Wind.Game, Game", "Entry", "from host!", 1);

    hostfxr->stop();
  } catch (const std::exception& ex) {
    spdlog::error(ex.what());
  }

  return EXIT_SUCCESS;
}