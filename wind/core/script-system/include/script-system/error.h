#pragma once
#include <exception>
#include <string>

namespace wind {

class ScriptSystemError : public std::exception {
public:
  ScriptSystemError(const std::string& message)
      : message(message) {
  }

  const char* what() const noexcept override {
    return message.c_str();
  }

private:
  const std::string message;
};

} // namespace wind
