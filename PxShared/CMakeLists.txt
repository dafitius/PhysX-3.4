cmake_minimum_required(VERSION 3.15)

project("PxShared")

set(PXSHARED_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory("./src/foundation")
add_subdirectory("./src/pvd")
add_subdirectory("./src/task")
add_subdirectory("./src/fastxml")