project(kasok)
cmake_minimum_required(VERSION 3.0)
enable_testing()

add_definitions(-std=c++11 -pedantic -Wall)
include_directories(${PROJECT_SOURCE_DIR})

if(EXISTS "${PROJECT_SOURCE_DIR}/extlib/Catch2/single_include/catch.hpp")
    message(STATUS "Catch2 is already downloaded.")
else()
    message(STATUS "Catch2/single_include/catch.hpp does not exists. start downloading...")
    execute_process(COMMAND git submodule update --init --recursive
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    message(STATUS "done.")
endif()

add_subdirectory(sample)
add_subdirectory(tests)
