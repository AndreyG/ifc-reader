#pragma once

#include <ifc/FileFwd.h>
#include <ifc/Expression.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;

    struct MonadExpression
    {
        MonadExpression(ifc::File const* ifc, ifc::MonadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        ifc::MonadicOperator op() const;

        Expression argument() const;

        Declaration resolve() const;

    private:
        ifc::File const* ifc_;
        ifc::MonadExpression const* expr_;
    };
}
