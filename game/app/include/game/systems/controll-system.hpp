#include "breeze/breeze.hpp"
#include <glm/glm.hpp>

namespace game {

class ControllSystem : public wind::ISystem {
public:
  ControllSystem();
  ~ControllSystem() override;

  void update(wind::World& world) override;

private:
  glm::vec3 velocity;
};

} // namespace game