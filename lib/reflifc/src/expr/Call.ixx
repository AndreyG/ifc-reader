module;

#include <compare>

export module reflifc:CallExpression;

import :Expression;
import :TupleView;

import ifc;

namespace reflifc
{
    export struct CallExpression
    {
        CallExpression(ifc::File const* ifc, ifc::CallExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression operation() const { return { ifc_, expr_->operation }; }
        TupleExpressionView arguments() const { return { ifc_, ifc_->expression_lists()[expr_->arguments].contents }; }

        auto operator<=>(CallExpression const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::CallExpression const* expr_;
    };
}
