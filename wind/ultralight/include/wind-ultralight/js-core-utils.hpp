#pragma once
#include <JavaScriptCore/JSRetainPtr.h>

namespace wind {
std::string JSStringToStdString(JSStringRef jsString);

std::string JSValueToStdString(JSContextRef ctx, JSValueRef value);

std::string JSValueRefToString(JSContextRef context, JSValueRef value);

JSValueRef getJSValue(JSContextRef context, JSObjectRef object, const char* key, JSValueRef* exception = nullptr);

JSObjectRef getJSObject(JSContextRef context, JSObjectRef object, const char* key, JSValueRef* exception = nullptr);
} // namespace wind
