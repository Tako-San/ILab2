cmake_minimum_required(VERSION 3.15)
project(geom)

include_directories(g_obj)
include_directories(octree)

set(G_OBJ g_obj/vec.cpp
          g_obj/line.cpp
          g_obj/plane.cpp
          g_obj/triangle.cpp
          g_obj/box.cpp)

set(OCTREE octree/octnode.hh
           octree/octree.hh)

set(GEOM_LIB geom.cpp )

add_library(geom STATIC ${GEOM_LIB} ${G_OBJ} ${OCTREE})