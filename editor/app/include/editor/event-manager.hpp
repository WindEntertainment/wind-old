#pragma once
#include <JavaScriptCore/JSRetainPtr.h>
#include <boost/hana.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <utils/includes.h>

namespace editor {

// template <typename Struct>
// Struct jsonToStruct(std::string& json);

JSValueRef handleCppEvent(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount,
  const JSValueRef arguments[], JSValueRef* exception);

} // namespace editor
