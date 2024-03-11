#pragma once
#include <spdlog/spdlog.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

namespace wind {

template <typename... T>
void yamlError(const std::string&& _message, const YAML::Node& _node, T&&... args) {
  spdlog::error(fmt::format("{} line: {}, column: {}", _message, _node.Mark().line, _node.Mark().column));
}

template <typename... T>
void yamlWarn(const std::string&& _message, const YAML::Node& _node, T&&... args) {
  spdlog::warn(fmt::format("{} line: {}, column: {}", _message, fmt::make_format_args(args...), _node.Mark().line, _node.Mark().column));
}

} // namespace wind