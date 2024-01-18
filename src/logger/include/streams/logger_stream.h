#pragma once
#include <utils.h>

namespace wind
{
    namespace logger
    {
        class Stream
        {
        public:
            virtual void write(const string &msg) = 0;
        };
    }
}