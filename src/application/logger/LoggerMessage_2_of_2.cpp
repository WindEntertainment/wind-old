#include "./Logger.h"

namespace app {
    namespace _Logger {
        // 
        Logger::Message::Message(const Message& org) {
            this->m_last = true;
            this->m_message << org.m_message.str();
            this->m_color = org.m_color;
            this->m_tag = org.m_tag;
            this->m_parent = org.m_parent;
        }

        // 
        Logger::Message::Message(string tag, Logger* parent) {
            this->m_tag = tag;
            this->m_last = true;
            this->m_parent = parent;

            auto colors = &parent->settings->colors;
            if (colors->find(tag) != colors->end())
                this->m_color = (*colors)[tag];
            else if (tag == "begin" || tag == "end")
                this->m_color = (*colors)["section"];
            else
                this->m_color = LoggerColors::WHITE;
        }

        // print in output streams when destruct message 
        Logger::Message::~Message() {

            // print only last message 
            if (!m_last)
                return;

            // if it's begin section 
            bool begin = (m_tag == "begin");
            
            // if it's end section num_section -= 1
            m_parent->m_num_section -= (m_tag == "end");
            m_parent->m_num_section = // num section can't be less zero
                m_parent->m_num_section < 0 ? 0 : m_parent->m_num_section;

            // replace tags "begin" and "end" to "section"
            if (m_tag == "begin" || m_tag == "end")
                m_tag = "section";

            // offset. num_section * num_space_for_section
            string offset = string(
                m_parent->m_num_section *
                m_parent->settings->num_space_for_section, ' '
            );

            // message
            std::stringstream ss;

            // formation system part of message 
            string data = offset + "[" + std::to_string(clock()) + "]"
                                + "{" + m_tag + "} ";

            // formation user part of message
            string str = m_message.str();
            for (size_t i = 0; i < str.size(); ++i)
                if (str[i] == '\n') // set offsets for multiline message 
                    str.insert(i + 1, string(data.size(), ' '));

            // join system and user part of message
            ss << data << str << "\n";

            // output in console
            if (m_parent->settings->enable_console_output) {
                string txtColor = "\033[1;3" + _Utils::toString(m_color) + "m"; 
                std::cout << (txtColor + ss.str() + "\033[1;37m").c_str();
            }

            // output in file
            if (m_parent->settings->enable_file_output) {
                m_parent->m_file << ss.str();
                m_parent->m_file.flush();
            }

            // if section tag is begin
            m_parent->m_num_section += begin;
        }
    }
}