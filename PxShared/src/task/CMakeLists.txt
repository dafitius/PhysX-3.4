cmake_minimum_required(VERSION 3.15)

file(GLOB PxTask_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB PxTask_windows_files
        "${CMAKE_CURRENT_SOURCE_DIR}/src/windows/*.cpp"
    )
    list(APPEND PxTask_source_files ${PxTask_windows_files})
endif()

add_library(PxTask STATIC ${PxTask_source_files})
target_include_directories(
    PxTask PUBLIC
    ${PXSHARED_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src/foundation/include
)