#pragma once
#include "includes.h"
#include <bits/ranges_algo.h>
#include <ranges>

namespace wind {

namespace chrono = std::chrono;

template <typename C, typename T>
  requires requires(C c, T t) {
    c.find(t);
    c.end();
  }
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

static auto forEach = std::ranges::for_each;

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
