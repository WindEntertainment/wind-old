#pragma once
#include "utils.h"

namespace wind {
    namespace stdgame {        
        class Prefab {
        private:
            string m_name;
            dom::Container* m_source;

            void build();
        public:
            Prefab(string name, dom::Document*);
            Prefab(string name, dom::Container*);
            ~Prefab();

            entt::entity instance(entt::registry& registry);
        };
    }
}