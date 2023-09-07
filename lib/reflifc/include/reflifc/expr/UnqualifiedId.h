#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Name;
    struct Expression;

    struct UnqualifiedIdExpression
    {
        UnqualifiedIdExpression(ifc::File const* ifc, ifc::UnqualifiedId const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Name name() const;

        Expression resolution() const;

        auto operator<=>(UnqualifiedIdExpression const& other) const = default;

    private:
        friend std::hash<UnqualifiedIdExpression>;

        ifc::File const* ifc_;
        ifc::UnqualifiedId const* expr_;
    };
}

template<>
struct std::hash<reflifc::UnqualifiedIdExpression>
{
    size_t operator()(reflifc::UnqualifiedIdExpression object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
