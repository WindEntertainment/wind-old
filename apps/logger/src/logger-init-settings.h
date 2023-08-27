#pragma once

#include "logger-colors.h"

namespace app {
    namespace _Logger {
        struct LoggerInitSettings {
            string name = "std-logger";
            string path_to_save = "";
            bool enable_console_output = false;
            bool enable_file_output = false;
            uint num_space_for_section = 0;
            std::map<std::string, LoggerColors> colors = {
                { "error", LoggerColors::RED },
                { "section", LoggerColors::GREEN },
                { "warning", LoggerColors::YELLOW },
                { "debug", LoggerColors::BLUE },
                { "info", LoggerColors::WHITE }
            };
        };
    }
}