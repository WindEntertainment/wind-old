#pragma once
#include "breeze/breeze.hpp"
#include <glm/glm.hpp>

namespace game {

class PlayerSystem : public wind::ISystem {
public:
  PlayerSystem();
  ~PlayerSystem() override;

  void update(wind::World& world) override;

private:
  wind::Entity gameState = 0;
  glm::ivec2 clickPosition = {-1, -1};
};

} // namespace game