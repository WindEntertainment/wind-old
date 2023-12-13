#pragma once
#include "prefab/prefab.h"
#include "prefab/component_registry.h"

namespace wind {
    namespace breeze {
        struct GameParameters {
            string bundle = "";
            void (*window)(system::Window::WindowConfig* self) = nullptr;
        };

        class Game {
        public:
            int main(std::function<void(GameParameters* self)> args);
        };
    }
}