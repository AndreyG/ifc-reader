#pragma once

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Type;
    struct TupleExpressionView;

    struct ProductValueTypeExpression
    {
        ProductValueTypeExpression(ifc::File const& ifc, ifc::ProductValueTypeExpression const& expr)
            : ifc_(ifc)
            , expr_(expr)
        {
        }

        Type                structure() const;
        TupleExpressionView members() const;

    private:
        ifc::File const & ifc_;
        ifc::ProductValueTypeExpression const& expr_;
    };
}
