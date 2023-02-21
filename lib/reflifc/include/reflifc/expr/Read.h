#pragma once

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Expression;

    struct ReadExpression
    {
        ReadExpression(ifc::File const* ifc, ifc::ReadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression address() const;

    private:
        ifc::File const* ifc_;
        ifc::ReadExpression const* expr_;
    };
}
