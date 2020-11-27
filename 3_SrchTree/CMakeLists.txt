cmake_minimum_required(VERSION 3.15)
project(srch_tree)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

#add_executable(tree main_time.cc)
add_executable(tree main.cc)
# add_executable(tree test.cc)
