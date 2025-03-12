cmake_minimum_required(VERSION 3.15)

file(GLOB PhysX3Cooking_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/convex/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mesh/*.cpp"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB PhysX3Cooking_windows_files
        "${CMAKE_CURRENT_SOURCE_DIR}/src/windows/*.cpp"
    )
    list(APPEND PhysX3Cooking_source_files ${PhysX3Cooking_windows_files})
endif()

add_library(PhysX3Cooking STATIC ${PhysX3Cooking_source_files})
target_include_directories(
    PhysX3Cooking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/convex
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mesh

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include

    ${PHYSX_DIR}/Source/Common/src
    
    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Include/cooking
    ${PHYSX_DIR}/Source/GeomUtils/headers
    ${PHYSX_DIR}/Source/GeomUtils/src
    ${PHYSX_DIR}/Source/GeomUtils/src/common
    ${PHYSX_DIR}/Source/GeomUtils/src/mesh
    ${PHYSX_DIR}/Source/GeomUtils/src/convex
    ${PHYSX_DIR}/Source/GeomUtils/src/hf
    ${PHYSX_DIR}/Source/GeomUtils/src/intersection
)