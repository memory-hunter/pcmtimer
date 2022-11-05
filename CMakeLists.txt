cmake_minimum_required(VERSION 3.23)
project(pcmtimer)
set(CMAKE_CXX_STANDARD 17)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/pcm/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

include_directories(pcm/src)
link_directories(lib)

add_library(printer STATIC src/printer.cpp)

add_executable(pcmtimer src/pcmtimer.cpp)

target_link_libraries(pcmtimer PUBLIC pcm-lib restrictDriverAccess printer)

set_target_properties(pcmtimer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_custom_command(TARGET pcmtimer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/required/MSR.sys"
        $<TARGET_FILE_DIR:pcmtimer>)
add_custom_command(TARGET pcmtimer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/required/pcm-lib.dll"
        $<TARGET_FILE_DIR:pcmtimer>)