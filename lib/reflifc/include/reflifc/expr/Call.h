#pragma once

#include <ifc/ExpressionFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct TupleExpressionView;

    struct CallExpression
    {
        CallExpression(ifc::File const& ifc, ifc::CallExpression const& expr)
            : ifc_(ifc)
            , expr_(expr)
        {
        }

        Expression operation() const;
        TupleExpressionView arguments() const;

    private:
        ifc::File const & ifc_;
        ifc::CallExpression const& expr_;
    };
}
