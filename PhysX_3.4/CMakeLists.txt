cmake_minimum_required(VERSION 3.15)

project("PhysX")

# Common include paths across all configurations
set(PHYSX_INCLUDE_DIRS
    ${PHYSX_DIR}/Include/gpu
    ${PHYSX_DIR}/Source/PhysXGpu/include
    ${PHYSX_DIR}/Source/PhysX/src/device
    ${PHYSX_DIR}/Source/Common/include
    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include
    ${PXSHARED_DIR}/src/fastxml/include
    ${PXSHARED_DIR}/src/pvd/include
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Include/GeomUtils
    ${PHYSX_DIR}/Include/pvd
    ${PHYSX_DIR}/Include/particles
    ${PHYSX_DIR}/Include/cloth
    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Source/Common/src
    ${PHYSX_DIR}/Source/GeomUtils/headers
    ${PHYSX_DIR}/Source/GeomUtils/src
    ${PHYSX_DIR}/Source/GeomUtils/src/contact
    ${PHYSX_DIR}/Source/GeomUtils/src/common
    ${PHYSX_DIR}/Source/GeomUtils/src/convex
    ${PHYSX_DIR}/Source/GeomUtils/src/distance
    ${PHYSX_DIR}/Source/GeomUtils/src/sweep
    ${PHYSX_DIR}/Source/GeomUtils/src/gjk
    ${PHYSX_DIR}/Source/GeomUtils/src/intersection
    ${PHYSX_DIR}/Source/GeomUtils/src/mesh
    ${PHYSX_DIR}/Source/GeomUtils/src/hf
    ${PHYSX_DIR}/Source/GeomUtils/src/pcm
    ${PHYSX_DIR}/Source/GeomUtils/src/ccd
    ${PHYSX_DIR}/Source/LowLevel/API/include
    ${PHYSX_DIR}/Source/LowLevel/software/include
    ${PHYSX_DIR}/Source/LowLevel/common/include/pipeline
    ${PHYSX_DIR}/Source/LowLevel/common/include/math
    ${PHYSX_DIR}/Source/LowLevel/common/include/utils
    ${PHYSX_DIR}/Source/LowLevel/common/include/collision
    ${PHYSX_DIR}/Source/LowLevelAABB/include
    ${PHYSX_DIR}/Source/LowLevelDynamics/include
    ${PHYSX_DIR}/Source/LowLevelDynamics/src
    ${PHYSX_DIR}/Source/LowLevelParticles/include
    ${PHYSX_DIR}/Source/LowLevelCloth/include
    ${PHYSX_DIR}/Source/PhysX/src
    ${PHYSX_DIR}/Source/PhysX/src/buffering
    ${PHYSX_DIR}/Source/PhysX/src/particles
    ${PHYSX_DIR}/Source/PhysX/src/cloth
    ${PHYSX_DIR}/Source/SimulationController/include
    ${PHYSX_DIR}/Source/SimulationController/src
    ${PHYSX_DIR}/Source/SimulationController/src/particles
    ${PHYSX_DIR}/Source/PhysXCooking/src
    ${PHYSX_DIR}/Source/PhysXCooking/src/mesh
    ${PHYSX_DIR}/Source/PhysXCooking/src/convex
    ${PHYSX_DIR}/Source/SceneQuery/include
    ${PHYSX_DIR}/Source/PhysXMetaData/core/include
)

# Conditionally gather platform-specific files
# if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#     list(APPEND PxFoundation_source_files 
        
#     )
# elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#     file(GLOB PxFoundation_windows_files
#         "${CMAKE_CURRENT_SOURCE_DIR}/src/windows/*.cpp"
#     )
#     list(APPEND PxFoundation_source_files ${PxFoundation_windows_files})
# endif()


add_subdirectory("Source/PhysX")
add_subdirectory("Source/PhysXCharacterKinematic")
add_subdirectory("Source/PhysXVehicle")
add_subdirectory("Source/PhysXExtensions")
add_subdirectory("Source/SceneQuery")
add_subdirectory("Source/SimulationController")
if(PX_COOKING)
    add_subdirectory("Source/PhysXCooking")
endif()

add_subdirectory("Source/Common")
add_subdirectory("Source/LowLevel")
add_subdirectory("Source/LowLevelAABB")
add_subdirectory("Source/LowLevelDynamics")
add_subdirectory("Source/LowLevelCloth")
add_subdirectory("Source/LowLevelParticles")

# add_subdirectory("PsFastXml")