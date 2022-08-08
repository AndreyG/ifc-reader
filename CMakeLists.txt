project (ifc-reader)
cmake_minimum_required(VERSION 3.16)

add_subdirectory(lib/core)
add_subdirectory(lib/msvc)

OPTION(BUILD_IFC_READER_EXAMPLES "Build library usage example apps" OFF)

if (BUILD_IFC_READER_EXAMPLES)
    add_subdirectory(examples/dump-decls)
endif()