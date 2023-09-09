#include "logger/logger.h"
#include "logger/streams/console/console_stream.h"

int main(int argc, char** argv) {
    wind::logger::Logger log = wind::logger::Logger([](string&& tag, string&& msg, std::stringstream& out){
        out << "[" << tag << "] " << msg << "\n";
    }, new wind::logger::ConsoleStream());

    log.debug() << "Hi!";
    log.error() << "PANIC!";
}