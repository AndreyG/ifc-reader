module;

#include <functional>

export module reflifc:ProductValueTypeExpression;

import :Type;
import :TupleView;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct ProductValueTypeExpression
    {
        ProductValueTypeExpression(ifc::File const* ifc, ifc::ProductValueTypeExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Type                structure() const { return { ifc_, expr_->structure }; }
        TupleExpressionView members()   const { return { ifc_, expr_->members }; }

        auto operator<=>(ProductValueTypeExpression const& other) const = default;

    private:
        friend std::hash<ProductValueTypeExpression>;

        ifc::File const* ifc_;
        ifc::ProductValueTypeExpression const* expr_;
    };
}

template<>
struct std::hash<reflifc::ProductValueTypeExpression>
{
    size_t operator()(reflifc::ProductValueTypeExpression object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
