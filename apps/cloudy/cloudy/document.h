#include "object.h"

namespace wind {
    namespace cloudy {
        class Document final {
        private:
            std::list<Object*> m_pool; 

            Container* m_root;
        public:
            Document() {
                m_root = allocContainer();
            }

            ~Document() {
                for (auto obj : m_pool)
                    delete obj;
                m_pool.clear();
            }

            Value* allocValue(string _value) {
                auto obj = new Value(_value, this);
                m_pool.push_back(obj);
                return obj;
            }

            Container* allocContainer() {
                auto container = new Container(this);
                m_pool.push_back(container);
                return container;
            }

            inline Container* root() const {
                return m_root;
            }         
        };
    }
}