project(wind-script-system)

set(HEADERS
  ./include/script-system/script-system.h
  ./include/script-system/hostfxr.h
  ./include/script-system/declaration.h
)

set(SOURCES
  ./src/script-system.cpp
  ./src/hostfxr.cpp
  ./src/error.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

include_directories("$ENV{DOTNET_INCLUDES}")
target_link_libraries(${PROJECT_NAME} PUBLIC "$ENV{DOTNET_INCLUDES}/libnethost.a")

# internal depencencies

target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)

# extrenal depencencies

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)
