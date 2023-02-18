#include "reflifc/expr/Call.h"

#include "reflifc/Expression.h"
#include "reflifc/TupleView.h"

#include <ifc/File.h>
#include <ifc/Expression.h>

namespace reflifc
{
    Expression CallExpression::operation() const
    {
        return { ifc_, expr_.operation };
    }

    TupleExpressionView CallExpression::arguments() const
    {
        return { ifc_, ifc_.expression_lists()[expr_.arguments].contents };
    }
}
