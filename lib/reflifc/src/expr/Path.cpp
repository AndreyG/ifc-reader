#include "reflifc/expr/Path.h"

#include "reflifc/Expression.h"

#include <ifc/Expression.h>

namespace reflifc
{
    Expression PathExpression::scope() const
    {
        return { ifc_, expr_.scope };
    }

    Expression PathExpression::member() const
    {
        return { ifc_, expr_.member };
    }
}
