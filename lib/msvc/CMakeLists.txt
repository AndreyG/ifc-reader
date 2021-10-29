project (ifc-msvc)

find_package(nlohmann_json)

set(headers
  include/ifc/MSVCEnvironment.h
)

set(sources
    src/MSVCEnvironment.cpp
)

add_library(ifc-msvc STATIC ${sources} ${headers})

target_include_directories(ifc-msvc
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(ifc-msvc PUBLIC ifc-core PRIVATE nlohmann_json::nlohmann_json)
