module;

#include <functional>

export module reflifc:PathExpression;

import :Expression;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct PathExpression
    {
        PathExpression(ifc::File const* ifc, ifc::PathExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression scope() const    { return { ifc_, expr_->scope }; }
        Expression member() const   { return { ifc_, expr_->member }; }

        auto operator<=>(PathExpression const& other) const = default;

    private:
        friend std::hash<PathExpression>;

        ifc::File const* ifc_;
        ifc::PathExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::PathExpression>
{
    size_t operator()(reflifc::PathExpression object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
