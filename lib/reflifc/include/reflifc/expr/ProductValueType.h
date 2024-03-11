#pragma once

#include "reflifc/Expression.h"
#include "reflifc/HashCombine.h"
#include "reflifc/TupleView.h"
#include "reflifc/ViewOf.h"

#include <ifc/Expression.h>
#include <ifc/File.h>

namespace reflifc
{
    struct Type;

    struct ProductValueTypeExpression
    {
        ProductValueTypeExpression(ifc::File const* ifc, ifc::ProductValueTypeExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Type structure() const;

        ViewOf<Expression> auto members() const
        {
            return TupleExpressionView(ifc_, expr_->members) | std::views::transform([this] (Expression e)
            {
                return Expression(ifc_, ifc_->suboject_value_expressions()[e.index()].value);
            });
        }

        auto operator<=>(ProductValueTypeExpression const& other) const = default;

    private:
        friend std::hash<ProductValueTypeExpression>;

        ifc::File const* ifc_;
        ifc::ProductValueTypeExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::ProductValueTypeExpression>
{
    size_t operator()(reflifc::ProductValueTypeExpression object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
