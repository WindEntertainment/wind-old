#include "utils.h"

namespace soul_dungeon {
    class Level {
    public:
        virtual void update() = 0;
        virtual void build() = 0;
    };
}