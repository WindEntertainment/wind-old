#include "../transform/Transform.h"

namespace app {
    class World {
    private:
        std::list<Entity*> m_entity;
    public:
        void addEntity(Entity*);
        void removeEntity(Entity*);
        
        template <typename TComponent>
        std::list<TComponent*> findAllWithComponent(TComponent*);

    };
}