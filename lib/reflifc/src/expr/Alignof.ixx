module;

#include <compare>

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
