#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Expression;

    struct PathExpression
    {
        PathExpression(ifc::File const* ifc, ifc::PathExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression scope() const;
        Expression member() const;

        auto operator<=>(PathExpression const& other) const = default;

    private:
        friend std::hash<PathExpression>;

        ifc::File const* ifc_;
        ifc::PathExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::PathExpression>
{
    size_t operator()(reflifc::PathExpression const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
