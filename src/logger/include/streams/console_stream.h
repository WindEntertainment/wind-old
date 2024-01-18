#include <streams/logger_stream.h>

namespace wind
{
    namespace logger
    {
        class ConsoleStream : public Stream
        {
        public:
            void write(const string &msg) override;
        };
    }
}