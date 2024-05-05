#include "game/utils.hpp"

namespace game {

class GameWorld {
public:
  void load();
  void update();
  void unload();

private:
  World world;
};

} // namespace game