#include "./LoggerColors.h"

namespace app {
    namespace _Utils {
        string toString(_Logger::LoggerColors color) {
            return std::to_string((int)color);
        }
    }
}