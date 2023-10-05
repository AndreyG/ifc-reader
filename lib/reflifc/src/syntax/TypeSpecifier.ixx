module;

#include <compare>

export module reflifc:TypeSpecifier;

import :Syntax;

import ifc;

namespace reflifc
{
    export struct TypeSpecifierSyntax
    {
        TypeSpecifierSyntax(ifc::File const* ifc, ifc::TypeSpecifierSeq const& syntax)
            : ifc_(ifc)
            , syntax_(&syntax)
        {
        }

        Syntax typename_() const { return { ifc_, syntax_->typename_ }; }

        auto operator<=>(TypeSpecifierSyntax const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::TypeSpecifierSeq const* syntax_;
    };
}
