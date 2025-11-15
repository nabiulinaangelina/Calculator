cmake_minimum_required(VERSION 3.20)
project(cpp_calculator 
    VERSION 1.0
    DESCRIPTION "Extended console calculator"
    LANGUAGES CXX
)


# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing for the whole repository
enable_testing()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include shared dependency module (downloads dependencies once)
include(${CMAKE_SOURCE_DIR}/cmake/Dependencies.cmake)
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

add_subdirectory(src)
add_subdirectory(tests)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
