module;

#include <functional>
#include <ranges>

export module reflifc:TypeTraitIntrinsic;

import :Syntax;
import :TupleView;
import reflifc.ViewOf;
import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct TypeTraitIntrinsicSyntax
    {
        TypeTraitIntrinsicSyntax(ifc::File const* ifc, ifc::TypeTraitIntrinsicSyntax const& syntax)
            : ifc_(ifc)
            , syntax_(&syntax)
        {
        }

        ifc::Operator intrinsic() const
        {
            return syntax_->intrinsic;
        }

        ViewOf<Syntax> auto arguments() const
        {
            return TupleSyntaxView(ifc_, syntax_->arguments)
                | std::views::transform([] (Syntax syntax) { return syntax.as_type_template_argument(); });
        }

        auto operator<=>(TypeTraitIntrinsicSyntax const& other) const = default;

    private:
        friend std::hash<TypeTraitIntrinsicSyntax>;

        ifc::File const* ifc_;
        ifc::TypeTraitIntrinsicSyntax const* syntax_;
    };
}

template<>
struct std::hash<reflifc::TypeTraitIntrinsicSyntax>
{
    size_t operator()(reflifc::TypeTraitIntrinsicSyntax object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.syntax_);
    }
};
