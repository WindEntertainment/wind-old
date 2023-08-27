project(logger)

add_library(${PROJECT_NAME} STATIC
    ./src/logger_message_1_of_2.cpp
    ./src/logger_message_2_of_2.cpp
    ./src/logger-colors.cpp
    ./src/logger.cpp
)