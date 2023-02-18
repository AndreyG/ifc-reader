#include "reflifc/expr/Monad.h"

#include "reflifc/Declaration.h"
#include "reflifc/Expression.h"

namespace reflifc
{
    ifc::MonadicOperator MonadExpression::op() const
    {
        return expr_.op;
    }

    Expression MonadExpression::argument() const
    {
        return { ifc_, expr_.argument };
    }

    Declaration MonadExpression::resolve() const
    {
        return { ifc_, expr_.impl };
    }
}
