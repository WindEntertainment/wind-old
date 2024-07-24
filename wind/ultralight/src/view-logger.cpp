#include <spdlog/spdlog.h>
#include <wind-ultralight/ultralight.h>

#include <Ultralight/Ultralight.h>

namespace wind {

inline std::string ViewLogger::toUTF8(const ul::String& str) {
  ul::String8 utf8 = str.utf8();
  return std::string(utf8.data(), utf8.length());
};

inline const char* ViewLogger::stringify(ul::MessageSource source) {
  switch (source) {
  case ul::kMessageSource_XML:
    return "XML";
  case ul::kMessageSource_JS:
    return "JS";
  case ul::kMessageSource_Network:
    return "Network";
  case ul::kMessageSource_ConsoleAPI:
    return "ConsoleAPI";
  case ul::kMessageSource_Storage:
    return "Storage";
  case ul::kMessageSource_AppCache:
    return "AppCache";
  case ul::kMessageSource_Rendering:
    return "Rendering";
  case ul::kMessageSource_CSS:
    return "CSS";
  case ul::kMessageSource_Security:
    return "Security";
  case ul::kMessageSource_ContentBlocker:
    return "ContentBlocker";
  case ul::kMessageSource_Other:
    return "Other";
  default:
    return "";
  }
};

inline const char* ViewLogger::stringify(ul::MessageLevel level) {
  switch (level) {
  case ul::kMessageLevel_Log:
    return "Log";
  case ul::kMessageLevel_Warning:
    return "Warning";
  case ul::kMessageLevel_Error:
    return "Error";
  case ul::kMessageLevel_Debug:
    return "Debug";
  case ul::kMessageLevel_Info:
    return "Info";
  default:
    return "";
  }
};

void ViewLogger::OnAddConsoleMessage(
  ul::View* caller,
  const ul::ConsoleMessage& log) {

  auto source = log.source();
  auto level = log.level();
  auto message = log.message();
  auto source_id = log.source_id();
  auto line_number = log.line_number();
  auto column_number = log.column_number();

  spdlog::log(Ultralight::mapUltralightLogLevelToSpd(level), "[UL::Console]: [{}] {}", stringify(source), toUTF8(message));

  if (source == ul::kMessageSource_JS)
    spdlog::log(Ultralight::mapUltralightLogLevelToSpd(level), "[UL::Console]: ({}) @ line: {}, column: {})", toUTF8(source_id), line_number, column_number);

  std::cout << std::endl;
};

}; // namespace wind
