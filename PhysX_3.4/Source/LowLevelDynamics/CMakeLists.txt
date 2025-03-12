cmake_minimum_required(VERSION 3.15)

file(GLOB LowLevelDynamics_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(LowLevelDynamics STATIC ${LowLevelDynamics_source_files})
target_include_directories(
    LowLevelDynamics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include

    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Include/GeomUtils
    ${PHYSX_DIR}/Source/Common/src
    ${PHYSX_DIR}/Source/GeomUtils/src/pcm
    ${PHYSX_DIR}/Source/GeomUtils/src/contact
    ${PHYSX_DIR}/Source/LowLevel/API/include
    ${PHYSX_DIR}/Source/LowLevel/software/include
    ${PHYSX_DIR}/Source/LowLevel/common/include/pipeline
    ${PHYSX_DIR}/Source/LowLevel/common/include/utils
)