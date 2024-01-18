#include <streams/console_stream.h>

namespace wind
{
    namespace logger
    {
        void ConsoleStream::write(const string &_msg)
        {
            std::cerr << _msg;
        }
    }
}