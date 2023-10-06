cmake_minimum_required(VERSION 3.24)
project(BerylliumCore VERSION 0.1.0)

# CXX Standard
set(CMAKE_CXX_STANDARD 23)

# Options
option(BERYLLIUM_BUILD_SHARED_LIBS "Build Beryllium as shared libraries" ON)
option(BERYLLIUM_COPY_HEADERS "Copy Beryllium headers to Build directory" ON)

if (BERYLLIUM_BUILD_SHARED_LIBS)
    set(BERYLLIUM_LIB_TYPE SHARED)
    set(BUILD_SHARED_LIBS ON)
else ()
    set(BERYLLIUM_LIB_TYPE STATIC)
    set(BUILD_SHARED_LIBS OFF)
endif ()

# directories locations
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Beryllium include and source directories
set(BE_INCLUDE_DIR ${INCLUDE_DIR}/Beryllium)
set(BE_SOURCES_DIR ${SOURCES_DIR}/Beryllium)

set(BE_CORE_INCLUDE_DIR ${BE_INCLUDE_DIR}/Common)
set(BE_CORE_SOURCES_DIR ${BE_SOURCES_DIR}/Common)

set(BE_CONTRACTS_INCLUDE_DIR ${BE_INCLUDE_DIR}/Contracts)
set(BE_CONTRACTS_SOURCES_DIR ${BE_SOURCES_DIR}/Contracts)

set(BE_PLATFORM_INCLUDE_DIR ${BE_INCLUDE_DIR}/Platform)
set(BE_PLATFORM_SOURCES_DIR ${BE_SOURCES_DIR}/Platform)

# Sources and Headers
file(GLOB_RECURSE BE_CORE_SOURCES ${BE_CORE_SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE BE_CORE_HEADERS ${BE_CORE_INCLUDE_DIR}/*.hpp)

file(GLOB_RECURSE BE_CONTRACTS_SOURCES ${BE_CONTRACTS_SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE BE_CONTRACTS_HEADERS ${BE_CONTRACTS_INCLUDE_DIR}/*.hpp)

file(GLOB_RECURSE BE_PLATFORM_SOURCES ${BE_PLATFORM_SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE BE_PLATFORM_HEADERS ${BE_PLATFORM_INCLUDE_DIR}/*.hpp)

if (WIN32)
    file(GLOB_RECURSE BE_IMPLEMENTATION_SOURCES ${BE_SOURCES_DIR}/Windows/*.cpp)
    file(GLOB_RECURSE BE_IMPLEMENTATION_HEADERS ${BE_INCLUDE_DIR}/Windows/*.hpp)
elseif (UNIX)
    file(GLOB_RECURSE BE_IMPLEMENTATION_SOURCES ${BE_SOURCES_DIR}/Linux/*.cpp)
    file(GLOB_RECURSE BE_IMPLEMENTATION_HEADERS ${BE_INCLUDE_DIR}/Linux/*.hpp)
endif ()

# Library
add_library(${PROJECT_NAME}
        ${BE_CORE_SOURCES} ${BE_CORE_HEADERS}
        ${BE_CONTRACTS_SOURCES} ${BE_CONTRACTS_HEADERS}
        ${BE_PLATFORM_SOURCES} ${BE_PLATFORM_HEADERS}
        ${BE_IMPLEMENTATION_SOURCES} ${BE_IMPLEMENTATION_HEADERS}
)
add_library(Beryllium::Core ALIAS ${PROJECT_NAME})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

# Export symbols
target_compile_definitions(${PROJECT_NAME} PRIVATE BERYLLIUM_EXPORT_SYMBOLS)
if (BERYLLIUM_BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC BERYLLIUM_BUILD_SHARED_LIBS)
endif ()

# Platform
if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC BERYLLIUM_PLATFORM_WINDOWS)

    target_link_libraries(${PROJECT_NAME} Shlwapi.lib)
elseif (UNIX)
    target_compile_definitions(${PROJECT_NAME} PUBLIC BERYLLIUM_PLATFORM_LINUX)

    find_package(X11 REQUIRED)
    message(STATUS "X11_FOUND       = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES   = ${X11_LIBRARIES}")
    target_include_directories(${PROJECT_NAME} PRIVATE ${X11_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
endif ()

# Debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC BERYLLIUM_DEBUG)
endif ()

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION Build/lib)

# Copy include/ files to Build directory
if (BERYLLIUM_COPY_HEADERS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../include
    )
endif ()