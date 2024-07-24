#pragma once
#include "Ultralight/String.h"
#include "Ultralight/platform/Logger.h"
#include <Ultralight/Ultralight.h>
#include <spdlog/spdlog.h>

namespace wind {

namespace ul = ultralight;

class ULLogger : public ul::Logger {
public:
  void LogMessage(ul::LogLevel level, const ul::String& message) override {
    switch (level) {
    case ul::LogLevel::Info:
      spdlog::info("{}", message.utf8().data());
      break;
    case ultralight::LogLevel::Warning:
      spdlog::warn("{}", message.utf8().data());
      break;
    case ultralight::LogLevel::Error:
      spdlog::error("{}", message.utf8().data());
      break;
    }
  }
};

} // namespace wind