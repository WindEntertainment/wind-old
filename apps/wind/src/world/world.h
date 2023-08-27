#include "../transform/transform.h"

namespace app {
    class World {
    private:
        static std::list<Entity*> m_entity;
    public:
        static void addEntity(Entity*);
        static void removeEntity(Entity*);
        
        template <typename TComponent>
        static std::list<TComponent*> findAllWithComponent() {
            std::list<TComponent*> result;

            for (auto entity : m_entity) {
                auto component = entity->getComponent<TComponent>();
                if (component)
                    result.push_back(component);
            }

            return result;
        }
    };
}