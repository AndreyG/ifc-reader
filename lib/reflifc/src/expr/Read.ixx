module;

#include <functional>

export module reflifc:ReadExpression;

import :Expression;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    struct Expression;

    export struct ReadExpression
    {
        ReadExpression(ifc::File const* ifc, ifc::ReadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        Expression address() const { return { ifc_, expr_->address }; }

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
    size_t operator()(reflifc::ReadExpression object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
