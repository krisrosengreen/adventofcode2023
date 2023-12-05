cmake_minimum_required(VERSION 3.10)

project(aoc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(../../utils ../../utils_build)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(COPY input DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY test DESTINATION "${PROJECT_BINARY_DIR}")

add_executable(aoc main.cpp)

target_link_libraries(aoc PUBLIC Utils)

target_include_directories(aoc PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/../../utils")
