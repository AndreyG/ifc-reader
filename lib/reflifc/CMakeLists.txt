project (reflifc)

set(sources
    src/Attribute.cpp
    src/Chart.cpp
    src/Declaration.cpp
    src/Expression.cpp
    src/Name.cpp
    src/Syntax.cpp
    src/TemplateId.cpp
    src/TupleView.cpp
    src/Type.cpp
    src/decl/Enumeration.cpp
    src/decl/Function.cpp
    src/decl/ScopeDeclaration.cpp
    src/decl/ClassOrStruct.cpp
    src/decl/Specialization.cpp
    src/decl/Variable.cpp
)

file(GLOB interface_units
    src/*.ixx
    src/decl/*.ixx
    src/expr/*.ixx
    src/type/*.ixx
    src/syntax/*.ixx
)

add_library(reflifc)
target_sources(reflifc
  PRIVATE ${sources}
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES ${interface_units}
)


target_include_directories(reflifc
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(reflifc PUBLIC ifc-core)
