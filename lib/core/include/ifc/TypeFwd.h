#pragma once

#include <cstdint>

namespace ifc
{
    enum class TypeSort;
    using TypeIndex = AbstractReference<5, TypeSort>;

    struct FundamentalType;
    struct DesignatedType;
    struct SyntacticType;
    struct ExpansionType;
    struct QualifiedType;
    struct RvalueReference;
    struct LvalueReference;
    struct TupleType;
    struct FunctionType;
    struct ForallType;

    enum class Qualifiers : std::uint8_t;
}
