cmake_minimum_required(VERSION 3.24)
project(BerylliumUnix VERSION 0.1.0)

if (UNIX)
    # CXX Standard
    set(CMAKE_CXX_STANDARD 23)

    # directories locations
    set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

    find_package(X11 REQUIRED)

    if (X11_FOUND)
        message(STATUS "X11_FOUND       = ${X11_FOUND}")
        message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
        message(STATUS "X11_LIBRARIES   = ${X11_LIBRARIES}")
    else()
        message(FATAL_ERROR "X11_FOUND       = ${X11_FOUND}")
        message(FATAL_ERROR "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
        message(FATAL_ERROR "X11_LIBRARIES   = ${X11_LIBRARIES}")
        message(FATAL_ERROR "X11 required to run on UNIX systems")
    endif ()

    # system libraries
    set(BE_PLATFORM_SYSTEM_LIBRARIES ${X11_LIBRARIES})

    # Sources and Headers
    file(GLOB_RECURSE BE_PLATFORM_HEADERS ${INCLUDE_DIR}/*.hpp)
    file(GLOB_RECURSE BE_PLATFORM_SOURCES ${SOURCES_DIR}/*.cpp)

    add_library(${PROJECT_NAME}
            ${BE_PLATFORM_HEADERS} ${BE_PLATFORM_SOURCES}
    )
    add_library(Beryllium::Platform ALIAS ${PROJECT_NAME})

    # Include directories
    target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
    target_include_directories(${PROJECT_NAME} PRIVATE ${X11_INCLUDE_DIR})

    # Export symbols
    target_compile_definitions(${PROJECT_NAME} PRIVATE BE_PLATFORM_EXPORT_SYMBOLS)

    # Linking
    target_link_libraries(${PROJECT_NAME} Beryllium::Core ${BE_PLATFORM_SYSTEM_LIBRARIES})

    # Copy include/ files to Build directory
    if (BERYLLIUM_COPY_HEADERS)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../include
        )
    endif ()
endif ()