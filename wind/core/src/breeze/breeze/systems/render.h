#include "system.h"

namespace wind {
namespace breeze {
class Render : public wind::breeze::System {
private:
  wind::renderer::Renderer* m_renderer;

public:
  Render(wind::renderer::Renderer* _renderer);
  void update(entt::registry&) override;
};
} // namespace breeze
} // namespace wind