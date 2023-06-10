#include <iostream>
#include <glm/glm.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char** argv) {
    glm::vec2 a{1, 2};
    std::cout << "Hello! :" << a.x << "\n";
    std::cout << "Hihihi! \n";

    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
  
    return RUN_ALL_TESTS();
}  