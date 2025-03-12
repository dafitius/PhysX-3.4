cmake_minimum_required(VERSION 3.15)

file(GLOB PsFastXml_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(PsFastXml STATIC ${PsFastXml_source_files})
target_include_directories(
    PsFastXml PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PXSHARED_DIR}/include
    ${PXSHARED_DIR}/src/foundation/include
)
