cmake_minimum_required(VERSION 3.24)
project(Beryllium VERSION 0.1.0)

# CXX Standard
set(CMAKE_CXX_STANDARD 23)

# Build directories
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/Build/${CMAKE_BUILD_TYPE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

# Options
option(BERYLLIUM_BUILD_SHARED_LIBS "Build Beryllium as shared libraries" ON)
option(BERYLLIUM_COPY_HEADERS "Copy Beryllium headers to Build directory" ON)

if (BERYLLIUM_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON)
    add_compile_definitions(BE_BUILD_SHARED_LIBS)
else ()
    set(BUILD_SHARED_LIBS OFF)
endif ()

# Platform
if (WIN32)
    add_compile_definitions(BE_PLATFORM_WINDOWS)
elseif (Unix)
    add_compile_definitions(BE_PLATFORM_UNIX)
endif ()

# Debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(BE_DEBUG)
endif ()

add_subdirectory(Core)

if (WIN32)
    add_subdirectory(Windows)
elseif (Unix)
    add_subdirectory(Unix)
endif ()

add_subdirectory(App)

add_subdirectory(Tests)