#include "system.h"

namespace soul_dungeon {
    class Render : public System {
    public:
        void update(entt::registry&) override;
    };
}