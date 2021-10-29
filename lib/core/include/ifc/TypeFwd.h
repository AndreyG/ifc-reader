#pragma once

#include <cstdint>

namespace ifc
{
    struct FundamentalType;
    struct DesignatedType;
    struct SyntacticType;
    struct ExpansionType;
    struct QualifiedType;
    struct RvalueReference;
    struct LvalueReference;
    struct TupleType;
    struct FunctionType;

    enum class Qualifiers : std::uint8_t;
}
