project(ForTheRecord)

set(CMAKE_CXX_STANDARD 14)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

add_library( ForTheRecordLibrary STATIC ForTheRecord/NumberFrequencyManager.cpp )
add_executable( app ForTheRecord/main.cpp )
IF (WIN32)
    target_link_libraries( app ForTheRecordLibrary)
ELSE()
    target_link_libraries( app ForTheRecordLibrary pthread)
ENDIF()

include_directories(./ForTheRecord)
add_executable( test ForTheRecordTest/tests.cpp )
target_link_libraries( test ForTheRecordLibrary gtest_main )
