cmake_minimum_required(VERSION 3.15)

file(GLOB SimulationController_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/cloth/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/particles/*.cpp"
)

add_library(SimulationController STATIC ${SimulationController_source_files})
target_include_directories(
    SimulationController PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cloth
    ${CMAKE_CURRENT_SOURCE_DIR}/src/particles

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include

    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Include/GeomUtils
    ${PHYSX_DIR}/Include/cloth
    ${PHYSX_DIR}/Include/particles

    ${PHYSX_DIR}/Source/Common/src
    ${PHYSX_DIR}/Source/LowLevel/API/include
    ${PHYSX_DIR}/Source/PhysXGpu/include

    ${PHYSX_DIR}/Source/GeomUtils/headers
    ${PHYSX_DIR}/Source/GeomUtils/src
    ${PHYSX_DIR}/Source/GeomUtils/src/contact
    ${PHYSX_DIR}/Source/GeomUtils/src/pcm
    ${PHYSX_DIR}/Source/GeomUtils/src/convex
    ${PHYSX_DIR}/Source/GeomUtils/src/mesh
    ${PHYSX_DIR}/Source/GeomUtils/src/hf
    ${PHYSX_DIR}/Source/GeomUtils/src/ccd

    ${PHYSX_DIR}/Source/LowLevel/software/include
    ${PHYSX_DIR}/Source/LowLevel/common/include/pipeline
    ${PHYSX_DIR}/Source/LowLevel/common/include/utils
    ${PHYSX_DIR}/Source/LowLevelAABB/include
    ${PHYSX_DIR}/Source/LowLevelDynamics/include
    ${PHYSX_DIR}/Source/LowLevelParticles/include
    ${PHYSX_DIR}/Source/LowLevelCloth/include
)