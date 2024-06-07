project(game-tests)

find_package(doctest REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)

target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
target_link_options(${PROJECT_NAME} PRIVATE --coverage)

include_directories(${CMAKE_SOURCE_DIR}/game)

include(CTest)

add_test(NAME MyTest COMMAND ${PROJECT_NAME})
