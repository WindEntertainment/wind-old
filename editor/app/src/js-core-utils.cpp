#include "utils/includes.h"

#include <JavaScriptCore/JSRetainPtr.h>
#include <editor/js-core-utils.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <utils/utils.h>

namespace editor {
using json = nlohmann::json;

std::string JSStringToStdString(JSStringRef jsString) {
  size_t maxBufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
  std::vector<char> buffer(maxBufferSize);
  size_t actualSize = JSStringGetUTF8CString(jsString, buffer.data(), maxBufferSize);
  return std::string(buffer.data(), actualSize - 1);
}

std::string JSValueToStdString(JSContextRef ctx, JSValueRef value) {
  JSStringRef jsString = JSValueToStringCopy(ctx, value, nullptr);
  std::string result = JSStringToStdString(jsString);
  JSStringRelease(jsString);
  return result;
}

std::string JSValueRefToString(JSContextRef context, JSValueRef value) {
  JSStringRef jsStringRef = JSValueToStringCopy(context, value, NULL);

  size_t length = JSStringGetMaximumUTF8CStringSize(jsStringRef);

  char* utf8Buffer = new char[length];

  JSStringGetUTF8CString(jsStringRef, utf8Buffer, length);

  std::string result(utf8Buffer);

  delete[] utf8Buffer;
  JSStringRelease(jsStringRef);

  return result;
};

JSValueRef getJSValue(JSContextRef context, JSObjectRef object, const char* key, JSValueRef* exception) {
  JSStringRef jsKey = JSStringCreateWithUTF8CString(key);
  JSValueRef value = JSObjectGetProperty(context, object, jsKey, exception);
  JSStringRelease(jsKey);
  return value;
}

JSObjectRef getJSObject(JSContextRef context, JSObjectRef object, const char* key, JSValueRef* exception) {
  JSValueRef value = getJSValue(context, object, key);
  JSObjectRef valueObject = JSValueToObject(context, value, exception);
  return valueObject;
}
} // namespace editor
