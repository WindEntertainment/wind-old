#include "logger.h"

namespace wind {
    namespace logger {
        Logger::Logger(
            void (*_format)(
                const char*, const int,
                string&&, string&&,
                std::stringstream&
            ),
            Stream* _output_stream
        ) {
            format = _format;
            m_stream = _output_stream;
            
            time_t t = time(NULL);
            m_time_info = *localtime(&t);
        }  

        Logger::~Logger() {
            delete m_stream;
        }
    }
}