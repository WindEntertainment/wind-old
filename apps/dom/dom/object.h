#include "utils.h"

namespace wind {
    namespace doom {
        enum class TypeObject {
            NIL,
            VALUE,
            CONTAINER
        };

        class Object {
            friend class Document;
        private:
            TypeObject m_type = TypeObject::NIL;
        protected:
            Object(TypeObject type): m_type(type) {};
        public:
            inline TypeObject getType() const {
                return m_type;
            }

            inline bool isContainer() const {
                return m_type == TypeObject::CONTAINER;
            }

            inline bool isValue() const {
                return m_type == TypeObject::VALUE;
            }
        };

        class Value final : public Object {
            friend class Document;
        private:
            string m_value;

            Value(string value): Object(TypeObject::VALUE) {
                m_value = value;
            }
        public:
            inline string asString() const {
                return m_value;
            }

            inline int asInt() const {
                return std::stoi(m_value);   
            }

            inline unsigned int asUInt() const {
                return (unsigned int)std::stoul(m_value);
            }

            inline unsigned long asULong() const {
                return std::stoul(m_value);
            }

            inline unsigned long long asULongLong() const {
                return std::stoull(m_value);
            }

            inline long asLong() const {
                return std::stol(m_value);
            }

            inline long long asLongLong() const {
                return std::stoll(m_value);
            }

            inline float asFloat() const {
                return std::stof(m_value);
            }

            inline double asDouble() const {
                return std::stod(m_value);
            }

            inline long double asLongDouble() const {
                return std::stold(m_value);
            }
        };

        class Container final : public Object {
            friend class Document;
        private:
            map<string, Object*> m_objs;
            Container() : Object(TypeObject::CONTAINER) {}
        public:
            void addObject(string key, Object* object) {
                m_objs.insert(std::make_pair(
                    key, object
                ));
            }

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

            map<string, Object*>::iterator begin() {
                return m_objs.begin();
            }   

            map<string, Object*>::iterator end() {
                return m_objs.end();
            }         
        };  
    }
}