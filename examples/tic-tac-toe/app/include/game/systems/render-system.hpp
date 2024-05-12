#pragma once
#include "breeze/breeze.hpp"

namespace game {

class RenderSystem : public wind::ISystem {
public:
  void update(wind::World& world) override;
};

} // namespace game