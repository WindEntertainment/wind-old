#include "breeze/breeze.hpp"

namespace game {

class ControllSystem : public wind::ISystem {
public:
  void update(wind::World& world) override;
};

} // namespace game