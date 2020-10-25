cmake_minimum_required(VERSION 3.15)
project(cache)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CACHE main_lfu.cpp tst_lfu.cpp)
# set(CACHE main_bel.cpp tst_bel.cpp)

add_executable(cache ${CACHE})
