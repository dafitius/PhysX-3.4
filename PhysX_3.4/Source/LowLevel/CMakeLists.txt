cmake_minimum_required(VERSION 3.15)

file(GLOB LowLevel_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/API/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/software/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/src/collision/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/src/pipeline/*.cpp"
)


add_library(LowLevel STATIC ${LowLevel_source_files})
target_include_directories(
    LowLevel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/API/include

    ${CMAKE_CURRENT_SOURCE_DIR}/common/include/collision
    ${CMAKE_CURRENT_SOURCE_DIR}/common/include/pipeline
    ${CMAKE_CURRENT_SOURCE_DIR}/common/include/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/software/include

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include

    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Include/GeomUtils

    ${PHYSX_DIR}/Source/Common/src
    ${PHYSX_DIR}/Source/PhysXGpu/include

    ${PHYSX_DIR}/Source/GeomUtils/headers
    ${PHYSX_DIR}/Source/GeomUtils/src
    ${PHYSX_DIR}/Source/GeomUtils/src/contact
    ${PHYSX_DIR}/Source/GeomUtils/src/pcm
    ${PHYSX_DIR}/Source/GeomUtils/src/ccd
    ${PHYSX_DIR}/Source/GeomUtils/src/hf
    ${PHYSX_DIR}/Source/GeomUtils/src/mesh


    ${PHYSX_DIR}/Source/LowLevelDynamics/include
)
