cmake_minimum_required(VERSION 3.13)
project(pntr_assetsys
    DESCRIPTION "pntr_assetsys: Load pntr assets from zip files with assetsys, a file system abstraction library."
    HOMEPAGE_URL "https://github.com/robloach/pntr_assetsys"
    VERSION 0.1.0
    LANGUAGES C
)

# pntr_assetsys
add_library(pntr_assetsys INTERFACE)
target_include_directories(pntr_assetsys INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Options
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(PNTR_ASSETSYS_IS_MAIN TRUE)
else()
    set(PNTR_ASSETSYS_IS_MAIN FALSE)
endif()

option(PNTR_APP_BUILD_TEST "Example: Test" ${PNTR_ASSETSYS_IS_MAIN})

if (PNTR_APP_BUILD_TEST AND NOT EMSCRIPTEN)
    # Testing
    include(CTest)
    enable_testing()
    if (BUILD_TESTING)
        # set(CTEST_CUSTOM_TESTS_IGNORE
        #     pkg-config--static
        # )
        # Always print verbose output when tests fail if run using `make test`.
        list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
        add_subdirectory(test)
    endif()
endif()
