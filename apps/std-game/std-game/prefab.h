#pragma once
#include "utils.h"

namespace wind {
    namespace stdgame {        
        class Prefab {
        private:
            string m_name;
            doom::Container* m_source;

            void build();
        public:
            Prefab(string name, doom::Document*);
            ~Prefab();

            entt::entity instance(entt::registry& registry,  doom::Container* source=nullptr);
        };
    }
}