#include "reflifc/expr/Read.h"

#include "reflifc/Expression.h"

#include <ifc/Expression.h>

namespace reflifc
{
    Expression ReadExpression::address() const
    {
        return { ifc_, expr_.address };
    }
}
