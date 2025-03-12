cmake_minimum_required(VERSION 3.15)

file(GLOB PhysX3CharacterKinematic_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(PhysX3CharacterKinematic STATIC ${PhysX3CharacterKinematic_source_files})
target_include_directories(
    PhysX3CharacterKinematic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include

    ${PHYSX_DIR}/Source/Common/src
    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/characterkinematic
    ${PHYSX_DIR}/Include/extensions
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
    ${PHYSX_DIR}/Source/GeomUtils/headers
)