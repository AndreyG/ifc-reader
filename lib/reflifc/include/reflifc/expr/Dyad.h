#pragma once

#include <ifc/FileFwd.h>
#include <ifc/Expression.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;

    struct DyadExpression
    {
        DyadExpression(ifc::File const& ifc, ifc::DyadExpression const& expr)
            : ifc_(ifc)
            , expr_(expr)
        {
        }

        ifc::DyadicOperator op() const;

        Expression left()   const;
        Expression right()  const;

        Declaration resolve() const;

    private:
        ifc::File const & ifc_;
        ifc::DyadExpression const& expr_;
    };
}
