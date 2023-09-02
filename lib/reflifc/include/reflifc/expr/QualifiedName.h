#pragma once

#include "reflifc/HashCombine.h"

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

        auto operator<=>(QualifiedNameExpression const& other) const = default;

    private:
        friend std::hash<QualifiedNameExpression>;

        ifc::File const* ifc_;
        ifc::QualifiedNameExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::ProductValueTypeExpression>
{
    size_t operator()(reflifc::ProductValueTypeExpression const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
