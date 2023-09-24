module;

#include <functional>

export module reflifc:Sizeof;

import :Type;

import reflifc.HashCombine;

import ifc;

namespace reflifc
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

template<>
struct std::hash<reflifc::SizeofExpression>
{
    size_t operator()(reflifc::SizeofExpression object) const noexcept
    {
        return std::hash<reflifc::Type>{}(object.operand);
    }
};
