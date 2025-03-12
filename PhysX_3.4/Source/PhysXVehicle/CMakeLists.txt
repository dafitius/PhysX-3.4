cmake_minimum_required(VERSION 3.15)

file(GLOB PhysX3Vehicle_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/PhysXMetaData/src/*.cpp"
)

add_library(PhysX3Vehicle STATIC ${PhysX3Vehicle_source_files})
target_include_directories(
    PhysX3Vehicle PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PhysXMetaData/include

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include
    ${PXSHARED_DIR}/src/pvd/include

    ${PHYSX_DIR}/Source/Common/src
    ${PHYSX_DIR}/Source/PhysXExtensions/src/serialization/Xml

    ${PHYSX_DIR}/Source/PhysXMetaData/core/include
    ${PHYSX_DIR}/Source/PhysXMetaData/extensions/include
    
    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/vehicle
    ${PHYSX_DIR}/Include/extensions
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Include/cloth
)