cmake_minimum_required(VERSION 3.15)
project(Triangles)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(geom)

# add_subdirectory(/usr/src/googletest gtest)
add_subdirectory(geom)

# add_executable(main tst.cpp)
add_executable(main main.cpp)

target_link_libraries(main geom)
