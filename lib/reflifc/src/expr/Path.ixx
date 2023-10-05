module;

#include <compare>

export module reflifc:PathExpression;

import :Expression;

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
        ifc::File const* ifc_;
        ifc::PathExpression const* expr_;
    };
}
