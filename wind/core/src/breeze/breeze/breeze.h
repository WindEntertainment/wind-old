#pragma once
#include "prefab/component_registry.h"
#include "prefab/prefab.h"
#include "systems/system.h"

namespace wind {
namespace breeze {
struct GameParameters {
  string bundle = "";
  string scene = "";
  void (*window)(system::Window::WindowConfig* self) = nullptr;
};

class Game {
private:
  std::vector<System*> m_systems{};

public:
  void runSystem(System*);
  void stopSystem(System*);

  int main(std::function<void(GameParameters* self)> args);
};
} // namespace breeze
} // namespace wind