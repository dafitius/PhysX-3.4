cmake_minimum_required(VERSION 3.15)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(PXSHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PxShared)
set(PHYSX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PhysX_3.4)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(_DEBUG)
else()
    add_compile_definitions(NDEBUG)
endif()


option(PX_COOKING "Enable PhysX cooking feature" ON)
option(PX_CHECKED "Enable PhysX runtime checking feature" ON)
option(PX_SUPPORT_PVD "Enable PhysX pvd feature" OFF)
option(PX_PHYSX_STATIC_LIB "Enable static linking for PhysX" ON)
option(DISABLE_CUDA_PHYSX "Disable PhysX GPU feature" ON)


if(DEFINED CMAKE_CXX_FLAGS)
    string(REPLACE "-DPX_COOKING" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "-DPX_CHECKED" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "-DPX_SUPPORT_PVD" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "-DPX_PHYSX_STATIC_LIB" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "-DDISABLE_CUDA_PHYSX" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()


if(PX_COOKING)
    add_compile_definitions(PX_COOKING)
endif()

if(PX_CHECKED)
    add_compile_definitions(PX_CHECKED)
endif()

if(PX_SUPPORT_PVD)
    add_compile_definitions(PX_SUPPORT_PVD)
endif()

if(PX_PHYSX_STATIC_LIB)
    add_compile_definitions(PX_PHYSX_STATIC_LIB)
endif()

if(DISABLE_CUDA_PHYSX)
    add_compile_definitions(DISABLE_CUDA_PHYSX)
endif()

add_subdirectory(PxShared)
add_subdirectory(PhysX_3.4)
