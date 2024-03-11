project (ifc-reader)
cmake_minimum_required(VERSION 3.16)

OPTION(BUILD_IFC_READER_EXAMPLES "Build library usage example apps" OFF)
OPTION(BUILD_IFC_READER_TESTS "Build tests" OFF)

add_subdirectory(lib/core)
add_subdirectory(lib/reflifc)

if (BUILD_IFC_READER_EXAMPLES OR BUILD_IFC_READER_TESTS)
    add_subdirectory(lib/msvc)
    add_subdirectory(lib/blob-reader)
endif()

if (BUILD_IFC_READER_EXAMPLES)
    add_subdirectory(examples/dump-decls)
endif()

if (BUILD_IFC_READER_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()
