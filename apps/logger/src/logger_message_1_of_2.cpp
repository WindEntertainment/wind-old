#include "logger.h"

namespace app {
    namespace _Logger {
        // myLogger->write("MyTag") << "Hello, World!"; 
        Logger::Message Logger::write(string tag) {
            return Logger::Message(tag, this);
        }

        // myLogger->info() << "Info message";
        Logger::Message Logger::info() {
            return write("info");
        } 

        // myLogger->debug() << "Debug message";
        Logger::Message Logger::debug() {
            return write("debug");
        }

        //
        Logger::Message Logger::error() {
            return write("error");
        }

        //
        Logger::Message Logger::warning() {
            return write("warning");
        }

        //
        Logger::Message Logger::sectionBegin() {
            return write("begin");
        }

        //
        Logger::Message Logger::sectionEnd() {
            return write("end");
        }
    }
}