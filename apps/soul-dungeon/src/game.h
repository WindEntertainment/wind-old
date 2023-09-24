#pragma once
#include "level.h"

#include <asset-bundler/bundle.h>
#include <renderer/renderer.h>
#include <system/window.h>
#include <entt/entity/registry.hpp>

namespace soul_dungeon {
    class Game {
    private:
        static Game* singlton;
        
        assets::Bundle* m_bundle;
        system::Window* m_window;
        renderer::Renderer* m_renderer;
        entt::registry* m_registry;
    public:
        static assets::Bundle* bundle();
        static renderer::Renderer* renderer();
        static system::Window* window();
        static entt::registry* registry();

        int play(Level*);
    };
}