#include "breeze/breeze.hpp"

namespace game {

class MoveSystem : public wind::ISystem {
public:
  void update(wind::World& world) override;
};

} // namespace game