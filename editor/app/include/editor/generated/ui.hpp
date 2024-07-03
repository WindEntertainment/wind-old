#pragma once
#include <editor/event-manager.hpp>
#include <utils/includes.h>
#include <utils/utils.h>

namespace JsEvents {

namespace LoadProject {
struct Input {
  std::string name;
  long createdAt;
  std::string maps;
};
struct Output {
  bool success;
};
} // namespace LoadProject
class Methods {
public:
  LoadProject::Output loadProject(const LoadProject::Input& input, JSContextRef context);
};
}; // namespace JsEvents

namespace CppEvents {

namespace SaveProject {
struct Input {
  std::string name;
  int createdAt;
  std::string maps;
};
struct Output {
  bool success;
};
} // namespace SaveProject
class Methods {
public:
  SaveProject::Output saveProject(const SaveProject::Input& input);
};
}; // namespace CppEvents
