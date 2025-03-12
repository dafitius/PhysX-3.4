cmake_minimum_required(VERSION 3.15)

file(GLOB SceneQuery_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(SceneQuery STATIC ${SceneQuery_source_files})
target_include_directories(
    SceneQuery PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PHYSX_INCLUDE_DIRS}
)