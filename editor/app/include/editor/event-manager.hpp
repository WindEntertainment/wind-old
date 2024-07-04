#pragma once
#include <JavaScriptCore/JSRetainPtr.h>
#include <utils/includes.h>
#include <utils/utils.h>

namespace editor {

JSValueRef handleCppEvent(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount,
  const JSValueRef arguments[], JSValueRef* exception);

} // namespace editor
