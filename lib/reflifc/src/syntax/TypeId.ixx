module;

#include <compare>

export module reflifc:TypeId;

import :Syntax;
import :TypeSpecifier;

import ifc;

namespace reflifc
{
    export struct TypeIdSyntax
    {
        TypeIdSyntax(ifc::File const* ifc, ifc::TypeIdSyntax const& syntax)
            : ifc_(ifc)
            , syntax_(&syntax)
        {
        }

        TypeSpecifierSyntax type_specifier() const
        {
        	return Syntax(ifc_, syntax_->type_specifier).as_type_specifier();
        }

        auto operator<=>(TypeIdSyntax const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::TypeIdSyntax const* syntax_;
    };
}
