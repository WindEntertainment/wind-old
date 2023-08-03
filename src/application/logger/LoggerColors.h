#pragma once
#include "../../utlis.h"

namespace app {
    namespace _Logger {
        enum class LoggerColors {
            BLACK , RED  , GREEN,
            YELLOW, BLUE , COLOR1,
            COLOR2, WHITE 
        };
    }
    
    namespace _Utils {
        string toString(_Logger::LoggerColors color);
    }
}