project(logger)

add_library(${PROJECT_NAME} STATIC
    ./logger/logger.h
    ./logger/logger.cpp

    ./logger/message/logger_message_1_of_2.cpp
    ./logger/message/logger_message_2_of_2.cpp

    ./logger/streams/file/file_stream.h
    ./logger/streams/file/file_stream.cpp

    ./logger/streams/console/console_stream.h
    ./logger/streams/console/console_stream.cpp

    ./logger/streams/combine/combine_stream.h
    ./logger/streams/combine/combine_stream.cpp

    ./logger/utils.h
    ./logger/utils.cpp

    ./logger/wind_logger.h
    ./logger/wind_logger.cpp
)

include_directories(../logger/)