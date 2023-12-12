cmake_minimum_required(VERSION 3.10)

project(aoc)

file(COPY input DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY test DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY test2 DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY test3 DESTINATION "${CMAKE_BINARY_DIR}")

add_subdirectory(../../utils ../../utils_build)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_executable(aoc main.cpp)

target_link_libraries(aoc PUBLIC Utils)


target_include_directories(aoc PUBLIC
                        "${CMAKE_BINARY_DIR}"
                        "${CMAKE_SOURCE_DIR}/../../utils")
