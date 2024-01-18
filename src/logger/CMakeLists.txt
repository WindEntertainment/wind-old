project(logger)

set(HEADERS
    ./include/logger.h
    ./include/streams/file_stream.h
    ./include/streams/console_stream.h
    ./include/streams/combine_stream.h
    ./include/utils.h
    ./include/wind_logger.h
)

set(SOURCES
    ./src/logger.cpp
    ./src/wind_logger.cpp
    
    ./src/message/logger_message_1_of_2.cpp
    ./src/message/logger_message_2_of_2.cpp

    ./src/streams/file_stream.cpp
    ./src/streams/console_stream.cpp
    ./src/streams/combine_stream.cpp

    ./src/utils.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

include_directories(./include/)