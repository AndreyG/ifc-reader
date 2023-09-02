#pragma once

#include "reflifc/ViewOf.h"
#include "reflifc/Syntax.h"
#include "reflifc/TupleView.h"
#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/SyntaxTree.h>
#include <ifc/Name.h>

namespace reflifc
{
    struct TypeTraitIntrinsicSyntax
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
    size_t operator()(reflifc::TypeTraitIntrinsicSyntax const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.syntax_);
    }
};
