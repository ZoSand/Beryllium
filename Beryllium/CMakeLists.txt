cmake_minimum_required(VERSION 3.24)
project(Beryllium VERSION 0.1.0)

# CXX Standard
set(CMAKE_CXX_STANDARD 23)

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
elseif (UNIX)
    add_compile_definitions(BE_PLATFORM_UNIX)
endif ()

# Debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(BE_DEBUG)
endif ()

add_subdirectory(Core)

if (WIN32)
    add_subdirectory(Windows)
elseif (UNIX)
    add_subdirectory(Unix)
endif ()

add_subdirectory(App)