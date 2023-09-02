#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Type;
    struct TupleExpressionView;

    struct ProductValueTypeExpression
    {
        ProductValueTypeExpression(ifc::File const* ifc, ifc::ProductValueTypeExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Type                structure() const;
        TupleExpressionView members() const;

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
    size_t operator()(reflifc::ProductValueTypeExpression const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
