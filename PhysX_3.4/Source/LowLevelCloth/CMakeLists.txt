cmake_minimum_required(VERSION 3.15)

file(GLOB LowLevelCloth_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(LowLevelCloth STATIC ${LowLevelCloth_source_files})
target_include_directories(
    LowLevelCloth PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src

    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include

    ${PHYSX_DIR}/Include
    ${PHYSX_DIR}/Source/Common/src
)
