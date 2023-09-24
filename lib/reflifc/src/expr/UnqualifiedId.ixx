module;

#include <functional>

export module reflifc:UnqualifiedIdExpression;

import :Expression;
import :Name;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct UnqualifiedIdExpression
    {
        UnqualifiedIdExpression(ifc::File const* ifc, ifc::UnqualifiedId const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Name name() const { return { ifc_, expr_->name }; }

        Expression resolution() const { return { ifc_, expr_->resolution }; }

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
