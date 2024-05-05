#pragma once
#include <exception>
#include <string>

namespace wind {

class InputSystemError : public std::exception {
public:
  InputSystemError(const std::string& message)
      : message(message) {
  }

  const char* what() const noexcept override {
    return message.c_str();
  }

private:
  const std::string message;
};

} // namespace wind
