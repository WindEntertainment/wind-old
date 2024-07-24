#pragma once
#include <JavaScriptCore/JSRetainPtr.h>
#include <boost/hana.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <utils/includes.h>

#include "editor/event-manager.hpp"
#include "input-system/context.h"
#include "input-system/keys.h"
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
#include <wind-event-manager/convertor.hpp>
#include <wind-event-manager/emitter.hpp>
#include <wind-ultralight/ultralight.h>
#include <window/window.h>

namespace editor {
// template <typename Struct>
// Struct jsonToStruct(std::string& json);

JSValueRef handleCppEvent(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount,
  const JSValueRef arguments[], JSValueRef* exception);

} // namespace editor
