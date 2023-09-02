#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Expression;

    struct ReadExpression
    {
        ReadExpression(ifc::File const* ifc, ifc::ReadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression address() const;

        auto operator<=>(ReadExpression const& other) const = default;

    private:
        friend std::hash<ReadExpression>;

        ifc::File const* ifc_;
        ifc::ReadExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::ReadExpression>
{
    size_t operator()(reflifc::ReadExpression const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
