cmake_minimum_required(VERSION 3.26)
project (ifc-reader)

OPTION(BUILD_IFC_READER_EXAMPLES "Build library usage example apps" OFF)
OPTION(BUILD_IFC_READER_TESTS "Build tests" OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1) # enable dynamic dependency evaluation
#set(CMAKE_CXX_EXTENSIONS OFF) # required with Clang

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
