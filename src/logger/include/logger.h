#pragma once
#include "streams/logger_stream.h"

namespace wind
{
    namespace logger
    {
        enum class LoggerColors
        {
            BLACK,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            COLOR1,
            COLOR2,
            WHITE
        };

        class Logger
        {
        private:
            tm m_time_info;
            void (*format)(
                const char *, const int,
                string &&, string &&,
                std::stringstream &);

            Stream *m_stream;

        public:
            class Message
            {
            private:
                bool m_last;
                std::stringstream m_message;

                string m_tag;
                const char *m_file;
                int m_line;

                Logger *m_logger;

            public:
                Message(const Message &org);
                Message(
                    const char *file, const int line,
                    const string tag, Logger *parent);

                ~Message();

                template <typename T>
                Message operator<<(T value)
                {
                    this->m_last = false;
                    this->m_message << value;
                    return *this;
                }

                Message operator<<(bool value)
                {
                    this->m_last = false;
                    this->m_message << (value ? "true" : "false");
                    return *this;
                }
            };

        public:
            Logger(
                void (*format)(
                    const char *file, const int line,
                    string &&tag, string &&message,
                    std::stringstream &out),
                Stream *output_stream);
            ~Logger();

            Message write(const char *file, const int line, const string tag);

            Message INFO(const char *file, const int line);
            Message DEBUG(const char *file, const int line);
            Message WARNING(const char *file, const int line);
            Message _ERROR(const char *file, const int line);
        };
    }
}

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define info() INFO(__FILENAME__, __LINE__)
#define debug() DEBUG(__FILENAME__, __LINE__)
#define warning() WARNING(__FILENAME__, __LINE__)
#define error() _ERROR(__FILENAME__, __LINE__)