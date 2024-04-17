set(CPACK_BUNDLE_NAME "Dreich")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Dreich Inc")

if(WIN32)
    include(cpack/windows.cmake)
elseif(APPLE)
    include(cpack/macos.cmake)
else()
    include(cpack/linux.cmake)
endif()

include(CPack)
