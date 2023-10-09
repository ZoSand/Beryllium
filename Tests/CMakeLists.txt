########################################################################################################################
# Tests
########################################################################################################################

cmake_minimum_required(VERSION 3.24)
project(BerylliumTests VERSION 0.1.0)

# CXX Standard
set(CMAKE_CXX_STANDARD 23)

# target include directories
set(INCLUDE_DIR include)
set(SOURCES_DIR src)
include_directories(${INCLUDE_DIR})

set(TESTS_INCLUDE_DIR ${INCLUDE_DIR}/Test)
set(TESTS_SOURCES_DIR ${SOURCES_DIR}/Test)

# Sources and Headers
file(GLOB_RECURSE TESTS_SOURCES ${TESTS_SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE TESTS_HEADERS ${TESTS_INCLUDE_DIR}/*.hpp)

# Executable
add_executable(BerylliumTests ${TESTS_SOURCES} ${TESTS_HEADERS})

# Link
target_link_libraries(BerylliumTests Beryllium::Core Beryllium::Platform Beryllium::Application)

# Definitions

# Install
install(TARGETS BerylliumTests DESTINATION Build/bin)