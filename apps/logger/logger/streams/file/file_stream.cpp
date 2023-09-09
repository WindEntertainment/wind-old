#include "file_stream.h"

namespace wind {
    namespace logger {
        FileStream::~FileStream() {
            if (m_file.is_open())
                m_file.close();
        }
        
        FileStream::FileStream(const string&& _path) {
            m_file = std::ofstream(_path);
            if (!m_file.is_open()) {
                std::cerr << "Couldn't open file for write log:" << _path << "\n";
                return;
            }
        } 

        void FileStream::write(const string& _msg) {
            if (!m_file.is_open())
                return;
            
            m_file << _msg;
            m_file.flush();
        }
    }
}