project (ifc-core)

file(GLOB interface_units ./*.ixx)

add_library(ifc-core)
target_sources(ifc-core
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES ${interface_units}
)

target_compile_features(ifc-core PUBLIC cxx_std_20)
