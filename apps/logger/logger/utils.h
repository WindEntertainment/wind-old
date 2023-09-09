#pragma once
#include <iostream>

#include <map>
#include <vector>
#include <string>

#include <filesystem>
#include <fstream>
#include <sstream>

#ifdef _WIN32
    using uint = unsigned int;
#endif

using std::string;
using std::vector;
using std::map;

namespace fs = std::filesystem;

namespace wind {
    fs::directory_entry getOldestFileInDirectory(fs::path directory);
    size_t numberOfFilesInDirectory(fs::path path);
}