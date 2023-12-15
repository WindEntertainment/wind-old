#pragma once
#include "object.h"

namespace wind {
    namespace cloudy {
        class Value final : public Object {
            friend class Document;
        private:
            string m_value;

            Value(string value, Document* allocator): Object(TypeObject::VALUE, allocator) {
                m_value = value;
            }
        public:
            Object* copy(Document*) override;

            inline string asString() const                { return m_value; }
            inline int asInt() const                      { return std::stoi(m_value); }
            inline unsigned int asUInt() const            { return (unsigned int)std::stoul(m_value); }
            inline unsigned long asULong() const          { return std::stoul(m_value); }
            inline unsigned long long asULongLong() const { return std::stoull(m_value); }
            inline long asLong() const                    { return std::stol(m_value); }
            inline long long asLongLong() const           { return std::stoll(m_value); }
            inline float asFloat() const                  { return std::stof(m_value); }
            inline double asDouble() const                { return std::stod(m_value); }
            inline long double asLongDouble() const       { return std::stold(m_value); }
        };
    }
}