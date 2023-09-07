#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/ExpressionFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct TupleExpressionView;

    struct CallExpression
    {
        CallExpression(ifc::File const* ifc, ifc::CallExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression operation() const;
        TupleExpressionView arguments() const;

        auto operator<=>(CallExpression const& other) const = default;

    private:
        friend std::hash<CallExpression>;

        ifc::File const* ifc_;
        ifc::CallExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::CallExpression>
{
    size_t operator()(reflifc::CallExpression object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
