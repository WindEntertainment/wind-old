#include "wind_logger.h"

#include "streams/console_stream.h"
#include "streams/file_stream.h"
#include "streams/combine_stream.h"

namespace wind
{
    logger::Logger &log()
    {
        static auto log_format = [](
                                     const char *file, const int line,
                                     string &&tag, string &&msg, std::stringstream &out)
        {
            out << file << ":" << line << " [" << tag << "] " << msg << "\n";
        };

        static auto streams = new logger::CombineStream({new logger::ConsoleStream(),
                                                         new logger::FileStream("./logs/", []()
                                                                                {
                time_t now = time(0);
                return (const char*)ctime(&now); })});

        static logger::Logger log = wind::logger::Logger(log_format, streams);

        return log;
    }
}