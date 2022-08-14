#pragma once

#include <cstdint>

namespace ifc
{
    enum class TypeSort;
    using TypeIndex = AbstractReference<5, TypeSort>;

    struct FundamentalType;
    struct DesignatedType;
    struct TorType;
    struct SyntacticType;
    struct ExpansionType;
    struct PointerType;
    struct QualifiedType;
    struct RvalueReference;
    struct LvalueReference;
    struct TupleType;
    struct BaseType;
    struct FunctionType;
    struct MethodType;
    struct ForallType;
    struct SyntaxType;
    struct PlaceholderType;
    struct TypenameType;
    struct WordType;

    enum class Qualifiers : std::uint8_t;

    enum class FunctionTypeTraits : std::uint8_t;

    enum class TypeBasis : uint8_t;
}
