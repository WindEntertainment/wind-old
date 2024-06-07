project(wind-tests)

find_package(doctest REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-utils)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-input-system)

target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
target_link_options(${PROJECT_NAME} PRIVATE --coverage)

include(CTest)

add_test(NAME MyTest COMMAND ${PROJECT_NAME})
