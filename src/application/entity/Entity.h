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


        template <typename TComponent>
        TComponent* getComponent() {
            std::cout << typeid(TComponent).name() << "\n";
            for (auto component : m_components) {
                std::cout << typeid(component).hash_code() << "\n";
                if (typeid(component) == typeid(TComponent)) 
                    return (TComponent*)component;
            }
            return nullptr;
        }

        template <typename TComponent>
        bool hasComponent() {
            return (getComponent<TComponent>() != nullptr);
        }
    };
}