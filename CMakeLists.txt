# Initial stuff
cmake_minimum_required(VERSION 3.23)
project(pcmtimer VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PCM_DIR ${PROJECT_SOURCE_DIR}/pcm)
option(PCM_BUILD "Build the PCM library" OFF) # OFF for default

# Check and update for PCM if available
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
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/pcm/CMakeLists.txt")
        message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
    endif()
endif()

# Build the PCM library
if(PCM_BUILD)
    add_subdirectory(${PCM_DIR})
endif()

#Linking, includes and etc.
add_executable(pcmtimer src/pcmtimer.cpp)
set_target_properties(pcmtimer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_library(runner STATIC src/runner.cpp)
add_library(printer STATIC src/include/printer.h)
set_target_properties(printer PROPERTIES LINKER_LANGUAGE CXX)
add_library(algorithm_module STATIC src/include/algorithm/algorithm_module.h)
set_target_properties(algorithm_module PROPERTIES LINKER_LANGUAGE CXX)
add_library(algorithm_definitions STATIC src/include/algorithm/algorithm_definitions.h)
set_target_properties(algorithm_definitions PROPERTIES LINKER_LANGUAGE CXX)
add_library(time_units STATIC src/include/time_units.h)
set_target_properties(time_units PROPERTIES LINKER_LANGUAGE CXX)


target_link_directories(pcmtimer PUBLIC ${PROJECT_SOURCE_DIR}/lib)
target_include_directories(pcmtimer PUBLIC src/include src/include/algorithm ${PCM_DIR}/src)
target_include_directories(runner PUBLIC src/include/ src/include/algorithm ${PCM_DIR}/src)
target_link_libraries(pcmtimer PUBLIC pcm-lib restrictDriverAccess)

#Build the PCM if the .dll doesn't exist (for it to be up-to-date)
if (NOT EXISTS ${PROJECT_SOURCE_DIR}/required/pcm-lib.dll)
    add_subdirectory(${PCM_DIR})
    add_custom_command(TARGET pcmtimer PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/pcm-lib.dll"
            "${PROJECT_SOURCE_DIR}/required/")
endif()

# Copy the required files for the pcmtimer.exe
add_custom_command(TARGET pcmtimer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/required/MSR.sys"
        $<TARGET_FILE_DIR:pcmtimer>)
add_custom_command(TARGET pcmtimer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/required/pcm-lib.dll"
        "$<TARGET_FILE_DIR:pcmtimer>")