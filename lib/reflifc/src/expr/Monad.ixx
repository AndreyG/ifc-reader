module;

#include <compare>

export module reflifc:MonadExpression;

import :Declaration;
import :Expression;

import ifc;

namespace reflifc
{
    export struct MonadExpression
    {
        MonadExpression(ifc::File const* ifc, ifc::MonadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        ifc::MonadicOperator op() const { return expr_->op; }

        Expression argument() const { return { ifc_, expr_->argument }; }

        Declaration resolve() const { return { ifc_, expr_->impl }; }

        auto operator<=>(MonadExpression const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::MonadExpression const* expr_;
    };
}
