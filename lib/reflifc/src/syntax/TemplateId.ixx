module;

#include <functional>

export module reflifc:TemplateIdSyntax;

import :Syntax;
import :TupleView;

import reflifc.HashCombine;

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
        friend std::hash<TemplateIdSyntax>;

        ifc::File const* ifc_;
        ifc::TemplateIdSyntax const* syntax_;
    };
}

template<>
struct std::hash<reflifc::TemplateIdSyntax>
{
    size_t operator()(reflifc::TemplateIdSyntax object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.syntax_);
    }
};
