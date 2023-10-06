cmake_minimum_required(VERSION 3.24)
project(Beryllium VERSION 0.1.0)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/Build/${CMAKE_BUILD_TYPE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

add_subdirectory(Beryllium)
add_subdirectory(Tests)