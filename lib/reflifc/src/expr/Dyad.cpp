#include "reflifc/expr/Dyad.h"

#include "reflifc/Declaration.h"
#include "reflifc/Expression.h"

namespace reflifc
{
    ifc::DyadicOperator DyadExpression::op() const
    {
        return expr_.op;
    }

    Expression DyadExpression::left() const
    {
        return { ifc_, expr_.arguments[0] };
    }

    Expression DyadExpression::right() const
    {
        return { ifc_, expr_.arguments[1] };
    }

    Declaration DyadExpression::resolve() const
    {
        return { ifc_, expr_.impl };
    }
}
