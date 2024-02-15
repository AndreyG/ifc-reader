module;

#include <compare>

export module reflifc:Sizeof;

import :Type;

import ifc;

export namespace reflifc
{
    struct SizeofExpression
    {
        SizeofExpression(ifc::File const* ifc, ifc::SizeofExpression const& expr)
    		: operand(ifc, expr.operand)
        {}

        auto operator<=>(SizeofExpression const& other) const = default;

        Type operand;
    };
}
