#include "reflifc/expr/ProductValueType.h"

#include "reflifc/TupleView.h"
#include "reflifc/Type.h"

#include <ifc/Expression.h>

namespace reflifc
{
    Type ProductValueTypeExpression::structure() const
    {
        return { ifc_, expr_->structure };
    }

    TupleExpressionView ProductValueTypeExpression::members() const
    {
        return { ifc_, expr_->members };
    }
}
