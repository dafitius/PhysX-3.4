cmake_minimum_required(VERSION 3.15)

file(GLOB Pxpvd_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Conditionally gather platform-specific files
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB Pxpvd_windows_files
        "${CMAKE_CURRENT_SOURCE_DIR}/src/windows/*.cpp"
    )
    list(APPEND Pxpvd_source_files ${Pxpvd_windows_files})
endif()

add_library(PxPvdSDK STATIC ${Pxpvd_source_files})
target_include_directories(
    PxPvdSDK PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src/foundation/include
    ${PROJECT_SOURCE_DIR}/src/filebuf/include
    ${PROJECT_SOURCE_DIR}/../Externals/nvToolsExt/1/include
    ${PXSHARED_INCLUDE_DIRS}
)
