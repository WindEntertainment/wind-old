#include "World.h"

namespace app {
    //=========================================//
    
    void World::addEntity(Entity* _entity) {
        m_entity.push_back(_entity);
    }

    void World::removeEntity(Entity* _entity) {
        m_entity.remove(_entity);
    }

    //=========================================//

    template <typename TComponent>
    std::list<TComponent*> World::findAllWithComponent(TComponent* _component) {
        return std::list<TComponent*>();
    }
}