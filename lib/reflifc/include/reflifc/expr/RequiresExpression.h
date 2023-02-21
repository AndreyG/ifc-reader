#pragma once

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct RequiresExpression
    {
        RequiresExpression(ifc::File const* ifc, ifc::RequiresExpression const& expr)
            : ifc_(ifc)
            , expr_(expr)
        {
        }

    private:
        ifc::File const* ifc_;
        ifc::RequiresExpression const& expr_;
    };
}
