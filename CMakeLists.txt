# Initial stuff
cmake_minimum_required(VERSION 3.23)
project(pcmtimer VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PCM_DIR ${PROJECT_SOURCE_DIR}/pcm)
option(PCM_BUILD "Build the PCM library" OFF) # OFF for default

add_executable(pcmtimer src/pcmtimer.cpp
        src/algorithms/lca.cpp
        src/algorithms/bubble_sort.cpp)

# Check and update for PCM if available
find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif ()
    endif ()
    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/pcm/CMakeLists.txt")
        message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
    endif ()
endif ()

# Build the PCM library
if (PCM_BUILD)
    add_subdirectory(${PCM_DIR})
endif ()

#Build the PCM if the .dll or .libs doesn't exist (for it to be up-to-date)
if (NOT EXISTS ${PROJECT_SOURCE_DIR}/required/pcm-lib.dll
        OR NOT EXISTS ${PROJECT_SOURCE_DIR}/lib/pcm-lib.lib
        OR NOT EXISTS ${PROJECT_SOURCE_DIR}/lib/restrictDriverAccess.lib)
    add_subdirectory(${PCM_DIR})
    add_custom_command(TARGET pcmtimer PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_BINARY_DIR}/bin/$<CONFIG>/pcm-lib.dll"
            "${PROJECT_SOURCE_DIR}/required/")
        add_custom_command(TARGET pcmtimer PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "${PROJECT_SOURCE_DIR}/lib/")
    add_custom_command(TARGET pcmtimer PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_BINARY_DIR}/pcm/src/restrictDriverAccess.dir/$<CONFIG>/restrictDriverAccess.lib"
            "${PROJECT_SOURCE_DIR}/lib/")
    add_custom_command(TARGET pcmtimer PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_BINARY_DIR}/pcm/src/$<CONFIG>/pcm-lib.lib"
            "${PROJECT_SOURCE_DIR}/lib/")
endif ()

target_sources(pcmtimer PRIVATE src/runner.cpp src/algorithms/avl_trees.cpp src/algorithms/quick_sort.cpp src/algorithms/dijkstra.cpp)
target_link_directories(pcmtimer PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(pcmtimer PRIVATE pcm-lib restrictDriverAccess)
target_include_directories(pcmtimer PRIVATE src/include src/algorithms ${PCM_DIR}/src)
set_target_properties(pcmtimer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Copy the required files for the pcmtimer.exe
add_custom_command(TARGET pcmtimer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/required/MSR.sys"
        $<TARGET_FILE_DIR:pcmtimer>)
add_custom_command(TARGET pcmtimer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/required/pcm-lib.dll"
        "$<TARGET_FILE_DIR:pcmtimer>")