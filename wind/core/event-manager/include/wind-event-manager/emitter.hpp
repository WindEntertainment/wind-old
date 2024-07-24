#pragma once
#include <JavaScriptCore/JSRetainPtr.h>

namespace wind {

JSValueRef emitJSEvent(JSContextRef context, const char* event, JSValueRef* exception = nullptr);

} // namespace wind
