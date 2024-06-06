#pragma once
#include "breeze/breeze.hpp"

namespace game {

class EnemySystem : public wind::ISystem {
public:
  void update(wind::World& world) override;

private:
  wind::Entity gameState = 0;
};

} // namespace game