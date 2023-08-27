#include "entity.h"

namespace app {
    Entity::~Entity() {
        if (m_parent)
            m_parent->unbind(this);

        for (auto child : m_children)
            delete child;

        for (auto component : m_components)
            delete component;
    }

    //===================================================//

    void Entity::bind(Entity* _entity) {
        m_children.push_back(_entity);
    }

    void Entity::unbind(Entity* _entity) {
        m_children.remove(_entity);
    }

    //===================================================//

    void Entity::addComponent(Component* _component) {
        _component->m_entity = this;
        m_components.push_back(_component);
    }

    void Entity::removeComponent(Component* _component) {
        m_components.remove(_component);
    }
    
    //===================================================//
}