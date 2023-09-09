#include "logger/logger.h"
#include "logger/streams/console/console_stream.h"
#include "logger/streams/file/file_stream.h"
#include "logger/streams/combine/combine_stream.h"

int main(int argc, char** argv) {
    wind::logger::Logger log = wind::logger::Logger([](const char* file, const int line, string&& tag, string&& msg, std::stringstream& out){
        out << file << ":" << line << " [" << tag << "] " << msg << "\n";
    }, new wind::logger::CombineStream({
        new wind::logger::ConsoleStream(),
        new wind::logger::FileStream("./logs/log.txt")
    }));

    log.debug() << "hi!";
    log.error() << "error!";
    log.debug() << "hi!";
    log.error() << "fatal!";
    throw new std::exception();
    log.debug() << "hi!";  
}