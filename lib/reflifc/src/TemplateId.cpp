#include "reflifc/TemplateId.h"

#include "reflifc/Expression.h"
#include "reflifc/TupleView.h"

#include <ifc/Expression.h>

namespace reflifc
{
    Expression TemplateId::primary() const
    {
        return Expression(ifc_, template_id_.primary);
    }

    TupleExpressionView TemplateId::arguments() const
    {
        return { ifc_, template_id_.arguments };
    }
}
