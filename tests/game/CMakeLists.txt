project(game-tests)

# find_package(doctest REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

# target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)
# find_package(Boost 1.85.0 REQUIRED COMPONENTS unit_test_framework)
# target_link_libraries(tests Boost::unit_test_framework)
find_package(Boost REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC boost::boost)

target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
target_link_options(${PROJECT_NAME} PRIVATE --coverage)

include_directories(${CMAKE_SOURCE_DIR}/game)

include(CTest)

add_test(NAME MyTest COMMAND ${PROJECT_NAME})
