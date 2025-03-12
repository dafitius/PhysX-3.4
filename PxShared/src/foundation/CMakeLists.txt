cmake_minimum_required(VERSION 3.15)

file(GLOB PxFoundation_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(GLOB PxFoundation_unix_files
        "${CMAKE_CURRENT_SOURCE_DIR}/src/unix/*.cpp"
    )
    list(APPEND PxFoundation_source_files ${PxFoundation_unix_files})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB PxFoundation_windows_files
        "${CMAKE_CURRENT_SOURCE_DIR}/src/windows/*.cpp"
    )
    list(APPEND PxFoundation_source_files ${PxFoundation_windows_files})
endif()

add_library(PxFoundation STATIC ${PxFoundation_source_files})
target_include_directories(
    PxFoundation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PXSHARED_INCLUDE_DIRS}
    $<IF:$<STREQUAL:${CMAKE_SYSTEM_NAME},Linux>,${CMAKE_CURRENT_SOURCE_DIR}/include/unix,>
    $<IF:$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>,${CMAKE_CURRENT_SOURCE_DIR}/include/windows,>
)
