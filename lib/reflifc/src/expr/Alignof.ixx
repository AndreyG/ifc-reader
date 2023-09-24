module;

#include <functional>

export module reflifc:Alignof;

import :Type;

import ifc;

namespace reflifc
{
    export struct AlignofExpression
    {
        AlignofExpression(ifc::File const* ifc, ifc::AlignofExpression const& expr)
    		: operand(ifc, expr.operand)
        {}

        auto operator<=>(AlignofExpression const& other) const = default;

        Type operand;
    };
}

template<>
struct std::hash<reflifc::AlignofExpression>
{
    size_t operator()(reflifc::AlignofExpression object) const noexcept
    {
        return std::hash<reflifc::Type>{}(object.operand);
    }
};
