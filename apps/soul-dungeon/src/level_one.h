#include "game.h"

namespace soul_dungeon {
    class LevelOne : public Level {
    public:
        void build() override;
        void update() override;
        ~LevelOne();
    };
}