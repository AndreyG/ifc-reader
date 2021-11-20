project (ifc-core)

find_package(Boost REQUIRED COMPONENTS iostreams)

file(GLOB_RECURSE headers
  include/ifc/*.h
)

set(sources
    src/File.cpp
    src/Environment.cpp
    src/accessors.cpp
)

add_library(ifc-core STATIC ${sources} ${headers})

target_compile_features(ifc-core PUBLIC cxx_std_20)

target_include_directories(ifc-core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(ifc-core PRIVATE Boost::iostreams)
