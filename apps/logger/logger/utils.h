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
    fs::directory_entry getOldestFileInDirectory(fs::path directory) {
        fs::directory_entry oldest_file;
        for (auto file : fs::directory_iterator(directory)) {
            auto write_time = fs::last_write_time(file); 
            if (!oldest_file.exists() || write_time < fs::last_write_time(oldest_file))
                oldest_file = file;
        }
        return oldest_file;
    }

    size_t numberOfFilesInDirectory(fs::path path) {
        using std::filesystem::directory_iterator;
        return std::distance(directory_iterator(path), directory_iterator{});
    }
}