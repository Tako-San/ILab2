cmake_minimum_required(VERSION 3.15)
project(Triangles)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(../include ${GTEST_INCLUDE_DIRS})

include_directories(geom)
include_directories(geom/octree)

add_subdirectory(/usr/src/googletest gtest)
add_subdirectory(geom)

add_executable(trig main.cpp)
# add_executable(trig tst.cpp)

target_link_libraries(trig geom ${GTEST_LIBRARIES} Threads::Threads)
# target_link_libraries(trig geom)

enable_testing()