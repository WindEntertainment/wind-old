#pragma once
#include <fmt/core.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

namespace wind {

template <typename... T>
void yamlError(std::string _message, YAML::Node& _node, T&&... args) {
  spdlog::error(fmt::format("{}, {}", fmt::vformat(_message, fmt::make_format_args(args...)), fmt::format(" line: {}, column: {}", _node.Mark().line, _node.Mark().column)));
}

template <typename... T>
void yamlWarn(const char* _message, YAML::Node& _node, T&&... args) {
  spdlog::warn(fmt::format("{}, {}", fmt::vformat(_message, fmt::make_format_args(args...)), fmt::format(" line: {}, column: {}", _node.Mark().line, _node.Mark().column)));
}

} // namespace wind