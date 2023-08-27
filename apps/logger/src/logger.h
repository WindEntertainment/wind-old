#pragma once
#include "logger-init-settings.h"

namespace app {
    namespace _Logger {
        class Logger {
        private:
            LoggerInitSettings* settings;

            std::ofstream m_file;
            tm m_time_info;
            uint m_num_section;

            void close();
        public:
            class Message {
            private:
                bool m_last;
                std::stringstream m_message;
                string m_tag;
                LoggerColors m_color;
                
                Logger* m_parent;
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
            Logger(void (*config)(LoggerInitSettings* self));

            Message write(string tag);

            Message info();
            Message debug();
            Message warning();
            Message error();

            Message sectionBegin();
            Message sectionEnd();
    
            void file_output_init();
        };
    }

    _Logger::Logger* logger();
}