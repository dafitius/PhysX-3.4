cmake_minimum_required(VERSION 3.15)

file(GLOB LowLevelAABB_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(LowLevelAABB STATIC ${LowLevelAABB_source_files})
target_include_directories(
    LowLevelAABB PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include

    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry

    ${PHYSX_DIR}/Source/Common/src

    ${PHYSX_DIR}/Source/GeomUtils/headers
    ${PHYSX_DIR}/Source/GeomUtils/src
    ${PHYSX_DIR}/Source/LowLevel/common/include/utils
    ${PHYSX_DIR}/Source/LowLevel/API/include
)

