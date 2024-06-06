project(wind-tests)

find_package(Catch2 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/wind)

add_executable(wind-tests test.cpp main.cpp)

target_link_libraries(wind-tests PRIVATE Catch2::Catch2 -lpthread)

target_compile_options(wind-tests PRIVATE --coverage)
target_link_options(wind-tests PRIVATE --coverage)

include(CTest)
include(Catch)
catch_discover_tests(wind-tests)
