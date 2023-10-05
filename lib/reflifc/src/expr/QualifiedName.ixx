module;

#include <ranges>

export module reflifc:QualifiedNameExpression;

import :Expression;

import reflifc.ViewOf;

import ifc;

namespace reflifc
{
    struct Expression;

    export struct QualifiedNameExpression
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
