module;

#include <compare>

export module reflifc:TemplateIdSyntax;

import :Syntax;
import :TupleView;

import ifc;

namespace reflifc
{
    export struct TemplateIdSyntax
    {
        TemplateIdSyntax(ifc::File const* ifc, ifc::TemplateIdSyntax const& syntax)
            : ifc_(ifc)
            , syntax_(&syntax)
        {
        }

        Syntax name() const
        {
	        return { ifc_, syntax_->name };
        }

        TupleSyntaxView arguments() const
        {
	        return { ifc_, ifc_->template_argument_list_syntax_trees()[syntax_->arguments].arguments };
        }

        auto operator<=>(TemplateIdSyntax const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::TemplateIdSyntax const* syntax_;
    };
}
