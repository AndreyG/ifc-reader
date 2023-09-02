#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/Expression.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;

    struct DyadExpression
    {
        DyadExpression(ifc::File const* ifc, ifc::DyadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        ifc::DyadicOperator op() const;

        Expression left()   const;
        Expression right()  const;

        Declaration resolve() const;

        auto operator<=>(DyadExpression const& other) const = default;

    private:
        friend std::hash<DyadExpression>;

        ifc::File const* ifc_;
        ifc::DyadExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::DyadExpression>
{
    size_t operator()(reflifc::DyadExpression const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
