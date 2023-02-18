#include "reflifc/expr/Sizeof.h"

#include <ifc/Expression.h>

namespace reflifc
{
    SizeofExpression::SizeofExpression(ifc::File const& ifc, ifc::SizeofExpression const& expr)
        : operand(ifc, expr.operand)
    {
    }
}
