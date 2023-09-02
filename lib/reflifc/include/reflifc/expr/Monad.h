#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/Expression.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;

    struct MonadExpression
    {
        MonadExpression(ifc::File const* ifc, ifc::MonadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        ifc::MonadicOperator op() const;

        Expression argument() const;

        Declaration resolve() const;

        auto operator<=>(MonadExpression const& other) const = default;

    private:
        friend std::hash<MonadExpression>;

        ifc::File const* ifc_;
        ifc::MonadExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::MonadExpression>
{
    size_t operator()(reflifc::MonadExpression const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
