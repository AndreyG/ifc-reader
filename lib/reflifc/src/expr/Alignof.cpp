#include "reflifc/expr/Alignof.h"

#include <ifc/Expression.h>

namespace reflifc
{
    AlignofExpression::AlignofExpression(ifc::File const& ifc, ifc::AlignofExpression const& expr)
        : operand(ifc, expr.operand)
    {
    }
}
