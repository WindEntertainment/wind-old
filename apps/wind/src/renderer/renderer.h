#include "../world/world.h"

namespace wind {
    class Renderer {
    private:
        World* m_world;
    public:
        Renderer(World* _world);

        void render();
    };
}