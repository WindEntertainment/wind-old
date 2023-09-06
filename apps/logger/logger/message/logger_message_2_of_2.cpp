#include "logger/logger.h"

namespace wind {
    namespace logger {
        // 
        Logger::Message::Message(const Message& org) {
            this->m_last = true;
            this->m_message << org.m_message.str();
            this->m_tag = org.m_tag;
            this->m_logger = org.m_logger;
        }

        // 
        Logger::Message::Message(string tag, Logger* parent) {
            this->m_tag = tag;
            this->m_last = true;
            this->m_logger = parent;
        }

        // print in output streams when destruct message 
        Logger::Message::~Message() {
            if (!m_last)
                return;

            std::stringstream ss;
            m_logger->format(std::move(m_tag), m_message.str(), ss);
            m_logger->m_stream->write(ss.str());
        }
    }
}