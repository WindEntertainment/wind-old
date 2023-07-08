#include "../canvas/Canvas.h"

namespace app {
    class World {
    public:
        std::vector<vec2> vertex = {
            { 3, 1 }, { 4, 1 }, { 4, 2 }, { 3, 2 }
        };

        std::vector<vec2> lines = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}
        };

        glm::vec2 player = {1, 1};
        float alpha = 0.f;
    };
}