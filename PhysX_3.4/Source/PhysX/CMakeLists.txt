cmake_minimum_required(VERSION 3.15)

file(GLOB PhysX3_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/gpu/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/particles/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/buffering/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/cloth/*.cpp"
    "${PHYSX_DIR}/Source/ImmediateMode/src/*.cpp"
    "${PHYSX_DIR}/Source/PhysXMetaData/core/src/*.cpp"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(GLOB PhysX3_unix_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/device/linux/*.cpp"
    )
    list(APPEND PhysX3_source_files ${PhysX3_unix_files})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB PhysX3_windows_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/device/windows/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/windows/*.cpp"
    )
    list(APPEND PhysX3_source_files ${PhysX3_windows_files})
endif()

add_library(PhysX3 ${PhysX3_source_files})
target_link_libraries(PhysX3 PUBLIC SimulationController)
target_include_directories(
    PhysX3 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/buffering
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cloth
    ${CMAKE_CURRENT_SOURCE_DIR}/src/device
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/particles

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include
    ${PXSHARED_DIR}/src/pvd/include

    ${PHYSX_DIR}/Source/PhysXMetaData/core/include
    
    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/GeomUtils
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Include/cloth
    ${PHYSX_DIR}/Include/particles
    ${PHYSX_DIR}/Include/pvd
    ${PHYSX_DIR}/Include/gpu

    ${PHYSX_DIR}/Source/Common/src
    ${PHYSX_DIR}/Source/GeomUtils/headers
    ${PHYSX_DIR}/Source/GeomUtils/src
    ${PHYSX_DIR}/Source/GeomUtils/src/contact
    ${PHYSX_DIR}/Source/GeomUtils/src/pcm
    ${PHYSX_DIR}/Source/GeomUtils/src/mesh
    ${PHYSX_DIR}/Source/GeomUtils/src/convex
    ${PHYSX_DIR}/Source/GeomUtils/src/hf
    ${PHYSX_DIR}/Source/GeomUtils/src/intersection
    ${PHYSX_DIR}/Source/PhysXGpu/include
    ${PHYSX_DIR}/Source/LowLevel/API/include
    ${PHYSX_DIR}/Source/LowLevel/software/include
    ${PHYSX_DIR}/Source/LowLevel/common/include/pipeline
    ${PHYSX_DIR}/Source/LowLevelDynamics/include
    ${PHYSX_DIR}/Source/LowLevelParticles/include
    ${PHYSX_DIR}/Source/LowLevelAABB/include
    ${PHYSX_DIR}/Source/SimulationController/include
    ${PHYSX_DIR}/Source/SimulationController/src
    ${PHYSX_DIR}/Source/SimulationController/src/particles
    ${PHYSX_DIR}/Source/SceneQuery/include
)
