cmake_minimum_required(VERSION 3.23)
project(PlatformerEngine)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/includes)
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

include(GoogleTest)
include_directories(${PROJECT_INCLUDES_DIR}/spic-prj-api)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image SDL2::SDL2_mixer)
#target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)


file(GLOB_RECURSE SOURCE src/*.cpp ${PROJECT_INCLUDES_DIR}/spic-prj-api/*.cpp)
file(GLOB_RECURSE TEST_SOURCE tests/*.cpp tests/*.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

add_library(PlatformerEngine library.cpp)
