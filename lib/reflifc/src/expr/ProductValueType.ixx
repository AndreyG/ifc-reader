module;

#include <compare>

export module reflifc:ProductValueTypeExpression;

import :Type;
import :TupleView;

import ifc;

namespace reflifc
{
    export struct ProductValueTypeExpression
    {
        ProductValueTypeExpression(ifc::File const* ifc, ifc::ProductValueTypeExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Type                structure() const { return { ifc_, expr_->structure }; }
        TupleExpressionView members()   const { return { ifc_, expr_->members }; }

        auto operator<=>(ProductValueTypeExpression const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::ProductValueTypeExpression const* expr_;
    };
}
