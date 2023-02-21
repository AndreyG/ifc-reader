#pragma once

#include "reflifc/ViewOf.h"
#include "reflifc/Syntax.h"
#include "reflifc/TupleView.h"

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

    private:
        ifc::File const* ifc_;
        ifc::TypeTraitIntrinsicSyntax const* syntax_;
    };
}
