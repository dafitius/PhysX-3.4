cmake_minimum_required(VERSION 3.15)

file(GLOB PhysX3Extensions_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/serialization/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/serialization/Binary/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/serialization/Xml/*.cpp"
    "${PHYSX_DIR}/Source/PhysXMetaData/extensions/src/*.cpp"
)

add_library(PhysX3Extensions STATIC ${PhysX3Extensions_source_files})
target_include_directories(
    PhysX3Extensions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serialization
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serialization/Binary
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serialization/Xml
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serialization/File

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include
    ${PXSHARED_DIR}/src/pvd/include
    ${PXSHARED_DIR}/src/fastxml/include

    ${PHYSX_DIR}/Source/Common/src
    ${PHYSX_DIR}/Source/PhysX/src


    ${PHYSX_DIR}/Source/PhysXMetaData/core/include
    ${PHYSX_DIR}/Source/PhysXMetaData/extensions/include
    
    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/extensions
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Include/cloth
    ${PHYSX_DIR}/Include/pvd
)