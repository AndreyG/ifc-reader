module;

#include <functional>

export module reflifc:CallExpression;

import :Expression;
import :TupleView;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct CallExpression
    {
        CallExpression(ifc::File const* ifc, ifc::CallExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression operation() const { return { ifc_, expr_->operation }; }
        TupleExpressionView arguments() const { return { ifc_, ifc_->expression_lists()[expr_->arguments].contents }; }

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
