#pragma once
#include "streams/logger_stream.h"

namespace wind {
    namespace logger {
        enum class LoggerColors {
            BLACK , RED  , GREEN,
            YELLOW, BLUE , COLOR1,
            COLOR2, WHITE 
        };

        class Logger {
        private:
            tm m_time_info;  
            void (*format)(
                string&&, string&&,
                std::stringstream&
            );
            
            Stream* m_stream;
        public:
            class Message {
            private:
                bool m_last;
                std::stringstream m_message;
                string m_tag;
            
                Logger* m_logger;
            public:
                Message(const Message& org);
                Message(string tag, Logger* parent);
                ~Message();

                template <typename T>
                Message operator<<(T value) {
                    this->m_last = false;
                    this->m_message << value;
                    return *this;
                }

                Message operator<<(bool value) {
                    this->m_last = false;
                    this->m_message << (value ? "true" : "false");
                    return *this;
                }
            };
        public:
            Logger(
                void (*format)(
                    string&& tag, string&& message,
                    std::stringstream& out
                ),
                Stream* output_stream
            );
            ~Logger();

            Message write(string tag);

            Message info();
            Message debug();
            Message warning();
            Message error();
        };
    }
}