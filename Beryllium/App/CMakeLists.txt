cmake_minimum_required(VERSION 3.24)
project(BerylliumApp VERSION 0.1.0)

# CXX Standard
set(CMAKE_CXX_STANDARD 23)

# directories locations
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Sources and Headers
file(GLOB_RECURSE BE_APP_HEADERS ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE BE_APP_SOURCES ${SOURCES_DIR}/*.cpp)

# This is the only explicitly static library here
# because it contains the application entry point
add_library(${PROJECT_NAME} STATIC
        ${BE_APP_HEADERS} ${BE_APP_SOURCES}
)
add_library(Beryllium::Application ALIAS ${PROJECT_NAME})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

# Linking
target_link_libraries(${PROJECT_NAME} Beryllium::Core Beryllium::Platform)

# Copy include/ files to Build directory
if (BERYLLIUM_COPY_HEADERS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../include
    )
endif ()