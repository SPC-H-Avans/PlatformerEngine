cmake_minimum_required(VERSION 3.23) # https://decovar.dev/blog/2021/03/08/cmake-cpp-library/

project(PlatformerEngine VERSION 1.0
        DESCRIPTION "Minor Systems programming in C++ project game engine"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

### Target ###
add_library(${PROJECT_NAME} STATIC)

file(GLOB PRIVATE_SOURCES src/*.cpp)
target_sources(${PROJECT_NAME}
        PRIVATE
            ${PRIVATE_SOURCES}
        )

#### Include Directories ###
target_include_directories(${PROJECT_NAME}
        PRIVATE
            # where the library itself will look for its internal headers
            ${CMAKE_CURRENT_SOURCE_DIR}/src/hdrs
        PUBLIC
            # where top-level project will look for the library's public headers
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            # where external projects will look for the library's public headers
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

### Installation Path ###
if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX is not set\n"
            "Default value: ${CMAKE_INSTALL_PREFIX}\n"
            "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
            "${CMAKE_SOURCE_DIR}/install"
            CACHE PATH "Where the library will be installed to" FORCE
            )
else()
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX was already set\n"
        "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

### Public Headers ###
file(GLOB PUBLIC_HEADERS include/*.hpp)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

### Setup Libraries ###

# SDL2
set(SDL2_INCLUDE_DIR ./libs/SDL/include)
set(SDL2_LIB_DIR ./libs/SDL/lib/x64)

set(SDL2_IMAGE_INCLUDE_DIR ./libs/SDL_Image/include)
set(SDL2_IMAGE_LIB_DIR ./libs/SDL_Image/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

# Enet
set(ENET_DIR "${CMAKE_SOURCE_DIR}/libs/enet-1.3.17")
file(GLOB ENET_INCLUDE_FILES ${ENET_DIR}/include/enet/*.hpp)
file(GLOB ENET_INCLUDE_FILES ${ENET_DIR}/*.c)
add_library(enet STATIC ${ENET_INCLUDE_FILES} ${ENET_SOURCE_FILES})
include_directories(${ENET_INCLUDE_DIR})

# GTest
enable_testing()
add_subdirectory(libs/gtest-1.12.1)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(PlatformerEngine SDL2main SDL2 SDL2_image enet)
target_link_libraries(PlatformerEngine -static)

if (WIN32)
    link_libraries(wsock32 ws2_32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()







#[[add_custom_command(TARGET poc_mario_physics POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:poc_mario_physics>/Assets)]]






