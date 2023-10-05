module;

#include <compare>

export module reflifc:DyadExpression;

import :Declaration;
import :Expression;

import ifc;

namespace reflifc
{
    export struct DyadExpression
    {
        DyadExpression(ifc::File const* ifc, ifc::DyadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        ifc::DyadicOperator op() const { return expr_->op; }

        Expression left()   const { return { ifc_, expr_->arguments[0] }; }
        Expression right()  const { return { ifc_, expr_->arguments[1] }; }

        Declaration resolve() const { return { ifc_, expr_->impl }; }

        auto operator<=>(DyadExpression const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::DyadExpression const* expr_;
    };
}
