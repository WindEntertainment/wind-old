#include "../mesh/Mesh.h"

namespace app {
    struct Component {};

    class Entity {
    private:
        Entity* m_parent;
        std::list<Entity*> m_children;
        std::list<Component*> m_components;
    public:
        ~Entity();

        void bind(Entity*);
        void unbind(Entity*);
        
        void addComponent(Component*);
        void removeComponent(Component*);

        bool hasComponent(Component*);
    };
}