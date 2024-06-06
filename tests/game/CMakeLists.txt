project(game-tests)

find_package(Catch2 3 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/game)

add_executable(game-tests test.cpp main.cpp)

target_link_libraries(game-tests PRIVATE Catch2::Catch2 -lpthread)

target_compile_options(game-tests PRIVATE --coverage)
target_link_options(game-tests PRIVATE --coverage)

include(CTest)
include(Catch)
catch_discover_tests(game-tests)
