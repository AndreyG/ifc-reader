module;

#include <compare>

export module reflifc:UnqualifiedIdExpression;

import :Expression;
import :Name;

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
        ifc::File const* ifc_;
        ifc::UnqualifiedId const* expr_;
    };
}
