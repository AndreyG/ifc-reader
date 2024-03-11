#include "reflifc/expr/UnqualifiedId.h"

#include "reflifc/Expression.h"
#include "reflifc/Name.h"

#include <ifc/Expression.h>

namespace reflifc
{
    Name UnqualifiedIdExpression::name() const
    {
        return { ifc_, expr_->name };
    }

    Expression UnqualifiedIdExpression::resolution() const
    {
        return { ifc_, expr_->resolution };
    }
}
