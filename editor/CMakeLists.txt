project(editor)

set(HEADERS
  ./app/include/editor/utils.hpp
  ./app/include/editor/event-manager.hpp

  ./app/include/editor/generated/ui.hpp
)

set(SOURCES
  ./app/src/event-manager.cpp
  ./app/src/events.cpp

  ./app/src/main.cpp
)


add_wind_game(${PROJECT_NAME} "main;resources" ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ./app/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE wind-breeze)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-event-manager)
target_link_libraries(${PROJECT_NAME} PRIVATE wind-ultralight)


find_package(Boost REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC boost::boost)
