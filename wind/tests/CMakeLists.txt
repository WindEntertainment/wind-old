project(wind-tests)

create_test_sourcelist (Tests
  test.cpp
  test2.cpp
  )

add_executable (${PROJECT_NAME} ${Tests})

set (TestsToRun ${Tests})

foreach (test ${TestsToRun})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME ${TName} COMMAND test ${TName})
endforeach ()

find_package(Catch2 3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC Catch2::Catch2WithMain)