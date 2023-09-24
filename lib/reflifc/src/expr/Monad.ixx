module;

#include <functional>

export module reflifc:MonadExpression;

import :Declaration;
import :Expression;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct MonadExpression
    {
        MonadExpression(ifc::File const* ifc, ifc::MonadExpression const& expr)
            : ifc_(ifc)
            , expr_(&expr)
        {
        }

        ifc::MonadicOperator op() const { return expr_->op; }

        Expression argument() const { return { ifc_, expr_->argument }; }

        Declaration resolve() const { return { ifc_, expr_->impl }; }

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
    size_t operator()(reflifc::MonadExpression object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expr_);
    }
};
