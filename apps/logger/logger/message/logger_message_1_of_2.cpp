#include "logger/logger.h"

namespace wind {
    namespace logger {
        // myLogger->write("MyTag") << "Hello, World!"; 
        Logger::Message Logger::write(const char* _file, const int _line, const string tag) {
            return Logger::Message(_file, _line, tag, this);
        }

        // myLogger->info() << "Info message";
        Logger::Message Logger::INFO(const char* _file, const int _line) {
            return write(_file, _line, "info");
        } 

        // myLogger->debug() << "Debug message";
        Logger::Message Logger::DEBUG(const char* _file, const int _line) {
            return write(_file, _line, "debug");
        }

        //
        Logger::Message Logger::_ERROR(const char* _file, const int _line) {
            return write(_file, _line, "error");
        }

        //
        Logger::Message Logger::WARNING(const char* _file, const int _line) {
            return write(_file, _line, "warning");
        }
    }
}