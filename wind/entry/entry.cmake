function(add_wind_game TARGET_NAME BUNDLE_LIST)
    add_executable(${TARGET_NAME} ${ARGN})
    
    set(BUNDLES_TARGETS "")
    foreach(BUNDLE ${BUNDLE_LIST})
        add_custom_target(
            ${BUNDLE}_bundle ALL
            COMMAND wind-asset-bundler -b ${BUNDLE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/
            COMMENT "Build bundle: ${BUNDLE}"
        )   

        list(APPEND BUNDLES_TARGETS ${BUNDLE}_bundle)     
    endforeach()

    add_custom_target(${TARGET_NAME}_bundles ALL DEPENDS ${BUNDLES_TARGETS})

    add_custom_command(TARGET ${TARGET_NAME}_bundles POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res" "$<TARGET_FILE_DIR:${TARGET_NAME}>/res"
    )

    target_link_libraries(${TARGET_NAME} PRIVATE wind-core)
    add_dependencies(${TARGET_NAME} ${TARGET_NAME}_bundles)
endfunction()