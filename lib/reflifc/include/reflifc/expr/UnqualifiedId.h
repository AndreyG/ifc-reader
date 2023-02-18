#pragma once

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Name;
    struct Expression;

    struct UnqualifiedIdExpression
    {
        UnqualifiedIdExpression(ifc::File const& ifc, ifc::UnqualifiedId const& expr)
            : ifc_(ifc)
            , expr_(expr)
        {
        }

        Name name() const;

        Expression resolution() const;

    private:
        ifc::File const & ifc_;
        ifc::UnqualifiedId const& expr_;
    };
}
