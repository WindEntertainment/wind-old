#include <catch2/catch_session.hpp>

int main(int argc, char* argv[]) {
  // your setup ...

  int result = Catch::Session().run(argc, argv);

  // your clean-up...

  return result;
}

// lcov --capture --directory . --output-file coverage.info
// lcov --remove coverage.info '/usr/*' --output-file coverage.info
// genhtml coverage.info --output-directory out
