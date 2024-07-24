#pragma once
#include <JavaScriptCore/JSRetainPtr.h>
#include <boost/hana.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <utils/includes.h>

#include "input-system/context.h"
#include "input-system/keys.h"

#include "editor/event-manager.hpp"
#include "utils/includes.h"
#include "wind-ultralight/js-core-utils.hpp"
#include <JavaScriptCore/JSRetainPtr.h>
#include <algorithm>
#include <asset-manager/asset-manager.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/hana/keys.hpp>
#include <boost/hana/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/version.hpp>
#include <editor/generated/ui.hpp>
#include <functional>
#include <input-system/input-system.h>
#include <iostream>
#include <ostream>
#include <renderer/renderer.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <tuple>
#include <utils/utils.h>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

namespace JsEvents {
namespace LoadProject {
struct Input {
  std::string name;
  int createdAt;
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
  SaveProject::Output saveProject(const SaveProject::Input& input, JSContextRef context);
};
}; // namespace CppEvents
