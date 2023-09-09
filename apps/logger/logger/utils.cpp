#include "utils.h"

namespace wind {
    fs::directory_entry getOldestFileInDirectory(fs::path _directory) {
        fs::directory_entry oldest_file;
        for (auto file : fs::directory_iterator(_directory)) {
            auto write_time = fs::last_write_time(file); 
            if (!oldest_file.exists() || write_time < fs::last_write_time(oldest_file))
                oldest_file = file;
        }
        return oldest_file;
    }

    size_t numberOfFilesInDirectory(fs::path _path) {
        using std::filesystem::directory_iterator;
        return std::distance(directory_iterator(_path), directory_iterator{});
    }
}