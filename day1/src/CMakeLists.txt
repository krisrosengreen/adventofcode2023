cmake_minimum_required(VERSION 3.10)

project(AoC23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(../../utils ../../utils_build)

file(COPY input DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(aoc main.cpp)

target_link_libraries(aoc PUBLIC Utils)

target_include_directories(aoc PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/../../utils")
