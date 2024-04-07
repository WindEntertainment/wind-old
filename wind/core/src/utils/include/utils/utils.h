#pragma once
#include "includes.h"
#include <codecvt>
#include <locale>

namespace wind {

namespace chrono = std::chrono;

using uint = unsigned int;

template <typename C, typename T>
concept Container = requires(C c, T t) {
  c.find(t);
  c.end();
};

template <typename C, typename T>
  requires Container<C, T>
bool contains(C _container, T _value) {
  auto it = _container.find(_value);
  return it != _container.end();
}

template <class Error>
  requires std::derived_from<Error, std::exception>
void verify(auto value) {
  if (!value)
    throw new Error();
}

// static auto forEach = std::ranges::for_each;
template <typename Range, typename Func>
static auto forEach(const Range& range, Func func) {
  std::for_each(std::begin(range), std::end(range), func);
}

#ifdef _WIN32
static auto stringToWindowsString(std::string input) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
  std::wstring wide_string = converter.from_bytes(input);
  return wide_string;
}
#endif

class Stopwatch {
public:
  Stopwatch(const std::string& message)
      : message(message) {
    start_time = std::chrono::high_resolution_clock::now();
  }

  ~Stopwatch() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
    spdlog::info("{} took {} milliseconds", message, duration.count());
  }

private:
  std::string message;
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

} // namespace wind
