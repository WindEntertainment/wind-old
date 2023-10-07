#include <std-game/system.h>

namespace soul_dungeon {
    class Render : public stdgame::System {
    public:
        void update(entt::registry&) override;
    };
}