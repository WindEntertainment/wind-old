#include "world.h"

namespace app {
    //=========================================//
    
    std::list<Entity*> World::m_entity = std::list<Entity*>();

    void World::addEntity(Entity* _entity) {
        m_entity.push_back(_entity);
    }

    void World::removeEntity(Entity* _entity) {
        m_entity.remove(_entity);
    }

    //=========================================//
}