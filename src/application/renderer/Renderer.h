#include "../world/World.h"

namespace app {
    class Renderer {
    private:
        World* m_world;
        Canvas* m_canvas;

        float raycast(vec2 _camera, float _alpha);
    public:
        Renderer(Canvas* _canvas, World* _world);

        void render();
    };
}