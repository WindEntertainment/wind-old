#include "../canvas/Canvas.h"

namespace app {
    class World {
    public:
        std::vector<vec2> vertex = {
            { 5, 1 }, { 6, 1 }, { 6, 2 }, { 5, 2 },
            { 2, 4 }, { 2, 6 }, { 7, 6 }, { 7, 5 }, { 4, 5 }, { 3, 4 },
            { 0, 0 }, { 8, 0 }, { 8, 8 }, { 0, 8 }
        };





        std::vector<vec2> lines = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0},
            {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 4},
            {10, 11}, {11, 12}, {12, 13}, {13, 10}
        };

        glm::vec2 player = {3, 1};
        float alpha = 0.f;

        void update() {
            if (Keyboard::isKey(GLFW_KEY_LEFT))  alpha -= PI / 100;
            if (Keyboard::isKey(GLFW_KEY_RIGHT)) alpha += PI / 100;

            if (Keyboard::isKey(GLFW_KEY_W)) {
                player.x += glm::cos(alpha) / 50;
                player.y += glm::sin(alpha) / 50;
            }

            if (Keyboard::isKey(GLFW_KEY_S)) {
                player.x += -glm::cos(alpha) / 50;
                player.y += -glm::sin(alpha) / 50;
            }

            if (Keyboard::isKey(GLFW_KEY_A)) {  
                player.x += glm::cos(alpha - 90) / 50;
                player.y += glm::sin(alpha - 90) / 50;
            }

            if (Keyboard::isKey(GLFW_KEY_D)) {
                player.x += glm::cos(alpha + 90) / 50;
                player.y += glm::sin(alpha + 90) / 50;
            }
        }
    };
}