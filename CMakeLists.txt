cmake_minimum_required(VERSION 3.23)
project(pcmtimer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_executable(pcmtimer src/pcmtimer.cpp)

add_library(printer src/printer.hpp)
add_library(algorithm_container src/algorithm_container.hpp)
add_library(avl src/avl.cpp)
add_library(bubblesort src/bubblesort.cpp)
add_library(quicksort src/quicksort.cpp)
set_target_properties(printer PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(algorithm_container PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(avl PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(bubblesort PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(quicksort PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(pcmtimer PUBLIC pcm-lib restrictDriverAccess)

add_compile_options(-O0)

set_target_properties(pcmtimer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_custom_command(TARGET pcmtimer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/required/MSR.sys"
        $<TARGET_FILE_DIR:pcmtimer>)
add_custom_command(TARGET pcmtimer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/required/pcm-lib.dll"
        $<TARGET_FILE_DIR:pcmtimer>)