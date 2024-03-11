project (ifc-blob-reader)

find_package(Boost REQUIRED COMPONENTS iostreams)

set(headers
  include/ifc/blob_reader.h
)

set(sources
    src/blob_reader.cpp
)

add_library(ifc-blob-reader STATIC ${sources} ${headers})

target_include_directories(ifc-blob-reader
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(ifc-blob-reader PUBLIC ifc-core PRIVATE Boost::iostreams)
