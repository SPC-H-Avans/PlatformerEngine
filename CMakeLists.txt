cmake_minimum_required(VERSION 3.23)
project(platformer-engine)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/includes)
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(tinyxml CONFIG REQUIRED)
find_package(unofficial-enet CONFIG REQUIRED)

include(GoogleTest)
include_directories(${PROJECT_INCLUDES_DIR}/spic-prj-api/)
include_directories(${PROJECT_INCLUDES_DIR}/platformer-engine/)
include_directories(${PROJECT_SOURCE_DIR}/src/)

include(vcpkg_install_deps.cmake)
vcpkg_install_deps(MANIFEST_ROOT ${PROJECT_SOURCE_DIR})


file(GLOB_RECURSE SOURCE src/*.hpp src/*.cpp ${PROJECT_INCLUDES_DIR}/spic-prj-api/*.hpp ${PROJECT_INCLUDES_DIR}/spic-prj-api/*.cpp ${PROJECT_INCLUDES_DIR}/platformer-engine/*.hpp)
file(GLOB_RECURSE TEST_SOURCE tests/*.cpp tests/*.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image)
target_link_libraries(${PROJECT_NAME} PUBLIC $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)
target_link_libraries(${PROJECT_NAME} PUBLIC unofficial::enet::enet)

#add asio boost serialisaztion

find_package(Boost REQUIRED serialization)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost Boost::serialization)

#-lSDL2
include_directories(${SDL2_INCLUDE_DIRS})

set(PROJECT_NAME_TESTS ${PROJECT_NAME}-tests)
add_executable(${PROJECT_NAME_TESTS} ${TEST_SOURCE})
add_dependencies(${PROJECT_NAME_TESTS} ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME_TESTS} PRIVATE ${PROJECT_NAME} GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
gtest_discover_tests(${PROJECT_NAME_TESTS})
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial-tinyxml::unofficial-tinyxml)

add_executable(${PROJECT_NAME}-exec main.cpp)
target_link_libraries(${PROJECT_NAME}-exec ${PROJECT_NAME})

# add -fprofile-arcs -ftest-coverage -fPIC to CMAKE_CXX_FLAGS for tests
#only if env variable COVERAGE is set
if (DEFINED ENV{COVERAGE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -fPIC")
endif ()

# -static-libgcc -static-libstdc++ -static for static linking
if(WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()

