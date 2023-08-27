#include <iostream>

#include <map>
#include <string>

#include <filesystem>
#include <fstream>
#include <sstream>

#ifdef _WIN32
    using uint = unsigned int;
#endif

using string = std::string;
namespace fs = std::filesystem;