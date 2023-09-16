#include "world.h"

namespace wind {
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