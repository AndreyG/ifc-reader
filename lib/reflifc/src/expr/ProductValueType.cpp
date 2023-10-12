#include "reflifc/expr/ProductValueType.h"

#include "reflifc/Type.h"

namespace reflifc
{
    Type ProductValueTypeExpression::structure() const
    {
        return { ifc_, expr_->structure };
    }
}
