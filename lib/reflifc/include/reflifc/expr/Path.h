#pragma once

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Expression;

    struct PathExpression
    {
        PathExpression(ifc::File const* ifc, ifc::PathExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression scope() const;
        Expression member() const;

    private:
        ifc::File const* ifc_;
        ifc::PathExpression const* expr_;
    };
}
