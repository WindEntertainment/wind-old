#include <logger.h>

namespace wind
{
    namespace logger
    {
        //
        Logger::Message::Message(const Message &org)
        {
            this->m_last = true;
            this->m_message << org.m_message.str();
            this->m_tag = org.m_tag;
            this->m_logger = org.m_logger;
            this->m_file = org.m_file;
            this->m_line = org.m_line;
        }

        //
        Logger::Message::Message(const char *_file, const int _line, const string _tag, Logger *_parent)
        {
            m_tag = _tag;
            m_last = true;
            m_logger = _parent;
            m_file = _file;
            m_line = _line;
        }

        // print in output streams when destruct message
        Logger::Message::~Message()
        {
            if (!m_last)
                return;

            std::stringstream ss;
            m_logger->format(m_file, m_line, std::move(m_tag), m_message.str(), ss);
            m_logger->m_stream->write(ss.str());
        }
    }
}