module;

#include <compare>

export module reflifc:RequiresExpression;

import ifc;

export namespace reflifc
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
