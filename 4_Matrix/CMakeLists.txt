cmake_minimum_required(VERSION 3.15)
project(Matrix)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(../include ${GTEST_INCLUDE_DIRS})


add_subdirectory(/usr/src/googletest gtest)


add_executable(matr test.cpp)

target_link_libraries(matr ${GTEST_LIBRARIES} Threads::Threads)

enable_testing()