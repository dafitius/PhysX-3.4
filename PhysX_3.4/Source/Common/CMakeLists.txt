cmake_minimum_required(VERSION 3.15)

#making sure geomutils globals are set
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../GeomUtils)
set(GEOMUTILS_SOURCE_FILES
    "${PHYSX_DIR}/Source/GeomUtils/src/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/contact/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/common/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/convex/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/distance/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/sweep/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/gjk/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/intersection/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/mesh/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/hf/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/pcm/*.cpp"
    "${PHYSX_DIR}/Source/GeomUtils/src/ccd/*.cpp"
)

set(GEOMUTILS_INCLUDE_DIRS
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
    ${PHYSX_DIR}/Include/GeomUtils
)


file(GLOB PhysX3Common_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    ${GEOMUTILS_SOURCE_FILES}
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB PhysX3Common_windows_files
        "${CMAKE_CURRENT_SOURCE_DIR}/src/windows/*.cpp"
    )
    list(APPEND PhysX3Common_source_files ${PhysX3Common_windows_files})
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/windows
    )
endif()

message("${LowLevelParticles_source_files}")



add_library(PhysX3Common STATIC ${PhysX3Common_source_files})

target_include_directories(
    PhysX3Common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src

    ${GEOMUTILS_INCLUDE_DIRS}

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include

    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Include/common
    ${PHYSX_DIR}/Include/geometry
)

# target_link_libraries(PhysX3Common PUBLIC PxFoundation PxPvdSDK)
