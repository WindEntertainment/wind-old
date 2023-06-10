cmake_minimum_required(VERSION 3.22)

project(SoulDungeon)

add_executable(main ./main.cpp)

find_package(glm CONFIG REQUIRED)
target_link_libraries(main PRIVATE glm::glm)

enable_testing()
    
find_package(GTest CONFIG REQUIRED)
target_link_libraries(main PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain main)