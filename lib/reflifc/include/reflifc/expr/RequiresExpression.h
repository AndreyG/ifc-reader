#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct RequiresExpression
    {
        RequiresExpression(ifc::File const* ifc, ifc::RequiresExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        auto operator<=>(RequiresExpression const& other) const = default;

    private:
        friend std::hash<RequiresExpression>;

        ifc::File const* ifc_;
        ifc::RequiresExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::RequiresExpression>
{
    size_t operator()(reflifc::RequiresExpression object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
