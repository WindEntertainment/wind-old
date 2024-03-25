#pragma once
// clang-format off
#include <glad/glad.h>     // IWYU pragma: export
#include <GLFW/glfw3.h>    // IWYU pragma: export
#include <chrono>          // IWYU pragma: export
#include <iostream>        // IWYU pragma: export
#include <string>          // IWYU pragma: export
#include <vector>          // IWYU pragma: export
#include <filesystem>      // IWYU pragma: export
#include <list>            // IWYU pragma: export
#include <map>             // IWYU pragma: export
#include <fstream>         // IWYU pragma: export
#include <algorithm>       // IWYU pragma: export
#include <ranges>          // IWYU pragma: export
#include <sstream>         // IWYU pragma: export

#ifndef __APPLE__
#include <bits/ranges_algo.h> // IWYU pragma: export
#endif

#include <spdlog/spdlog.h> // IWYU pragma: export
#include <glm/glm.hpp>     // IWYU pragma: export

namespace fs = std::filesystem;

// clang-format on
