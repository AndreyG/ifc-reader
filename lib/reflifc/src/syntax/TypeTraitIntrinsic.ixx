module;

#include <compare>
#include <ranges>

export module reflifc:TypeTraitIntrinsic;

import :Syntax;
import :TupleView;
import reflifc.ViewOf;

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
        ifc::File const* ifc_;
        ifc::TypeTraitIntrinsicSyntax const* syntax_;
    };
}
