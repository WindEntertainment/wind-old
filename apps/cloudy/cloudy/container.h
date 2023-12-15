#pragma once
#include "object.h"

namespace wind {
    namespace cloudy {
        class Container final : public Object {
            friend class Document;
        private:
            map<string, Object*> m_objs;
            Container(Document* allocator) : Object(TypeObject::CONTAINER, allocator) {}
        public:
            Object* copy(Document*) override;
            void addObject(string key, Object* object);
            
            // inlines getters

            inline Object* getObject(string _key) const {
                if (m_objs.contains(_key))
                    return m_objs.at(_key);
                return nullptr;
            }


            inline bool hasMember(string _key) const {
                return m_objs.contains(_key);
            }

            inline Object* operator[](string _key) const {
                return getObject(_key);
            }

            inline size_t size() const {
                return m_objs.size();
            }

            // iterator

            map<string, Object*>::iterator begin() {
                return m_objs.begin();
            }   

            map<string, Object*>::iterator end() {
                return m_objs.end();
            }         

            //
        };  
    }
}