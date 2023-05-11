project (reflifc)

file(GLOB_RECURSE headers
  include/reflifc/*.h
)

set(sources
    src/Attribute.cpp
    src/Chart.cpp
    src/Declaration.cpp
    src/Expression.cpp
    src/Name.cpp
    src/StringLiteral.cpp
    src/Syntax.cpp
    src/TemplateId.cpp
    src/TupleView.cpp
    src/Type.cpp
    src/Word.cpp
    src/decl/AliasDeclaration.cpp
    src/decl/Concept.cpp
    src/decl/DeclarationReference.cpp
    src/decl/Enumeration.cpp
    src/decl/Enumerator.cpp
    src/decl/Field.cpp
    src/decl/Function.cpp
    src/decl/Parameter.cpp
    src/decl/ScopeDeclaration.cpp
    src/decl/ClassOrStruct.cpp
    src/decl/TemplateDeclaration.cpp
    src/decl/UsingDeclaration.cpp
    src/decl/Variable.cpp
    src/expr/Alignof.cpp
    src/expr/Call.cpp
    src/expr/Dyad.cpp
    src/expr/Monad.cpp
    src/expr/Path.cpp
    src/expr/ProductValueType.cpp
    src/expr/Read.cpp
    src/expr/UnqualifiedId.cpp
    src/expr/Sizeof.cpp
    src/syntax/TemplateId.cpp
    src/syntax/TypeId.cpp
    src/syntax/TypeSpecifier.cpp
    src/type/Array.cpp
    src/type/Base.cpp
    src/type/Expansion.cpp
    src/type/Forall.cpp
    src/type/Function.cpp
    src/type/Placeholder.cpp
    src/type/Qualified.cpp
)

add_library(reflifc STATIC ${sources} ${headers})

target_include_directories(reflifc
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(reflifc PUBLIC ifc-core)
