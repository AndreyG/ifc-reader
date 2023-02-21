#pragma once

#include "reflifc/Expression.h"
#include "reflifc/ViewOf.h"

#include <ifc/File.h>

namespace reflifc
{
    struct Name;
    struct Expression;

    struct QualifiedNameExpression
    {
        QualifiedNameExpression(ifc::File const* ifc, ifc::QualifiedNameExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        ViewOf<Expression> auto parts() const
        {
            return get_qualified_name_parts(*ifc_, *expr_)
                | std::views::transform([ifc = ifc_] (ifc::ExprIndex part) { return Expression(ifc, part); });
        }

    private:
        ifc::File const* ifc_;
        ifc::QualifiedNameExpression const* expr_;
    };
}
