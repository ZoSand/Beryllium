cmake_minimum_required(VERSION 3.24)
project(BerylliumCore VERSION 0.1.0)

# CXX Standard
set(CMAKE_CXX_STANDARD 23)

# directories locations
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Sources and Headers
file(GLOB_RECURSE BE_CORE_HEADERS ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE BE_CORE_SOURCES ${SOURCES_DIR}/*.cpp)

add_library(${PROJECT_NAME}
        ${BE_CORE_HEADERS} ${BE_CORE_SOURCES}
)
add_library(Beryllium::Core ALIAS ${PROJECT_NAME})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

# Export symbols
target_compile_definitions(${PROJECT_NAME} PRIVATE BE_CORE_EXPORT_SYMBOLS)

# Copy include/ files to Build directory
if (BERYLLIUM_COPY_HEADERS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../include
    )
endif ()