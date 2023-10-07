#include <std-game/system.h>

namespace soul_dungeon {
    class Render : public wind::stdgame::System {
    public:
        void update(entt::registry&) override;
    };
}