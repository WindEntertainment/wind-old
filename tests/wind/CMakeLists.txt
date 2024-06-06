project(wind-tests)

# find_package(Catch2 REQUIRED)
find_package(doctest REQUIRED)

# add_executable(wind-tests test.cpp main.cpp)
# target_link_libraries(wind-tests PRIVATE Catch2::Catch2)
add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)

target_compile_options(wind-tests PRIVATE --coverage)
target_link_options(wind-tests PRIVATE --coverage)

include_directories(${CMAKE_SOURCE_DIR}/wind)


include(CTest)
add_test(NAME MyTest COMMAND wind-tests)
# include(Catch)
# catch_discover_tests(wind-tests)
