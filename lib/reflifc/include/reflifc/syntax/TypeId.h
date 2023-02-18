#pragma once

#include <ifc/FileFwd.h>
#include <ifc/SyntaxTreeFwd.h>

namespace reflifc
{
    struct TypeSpecifierSyntax;

    struct TypeIdSyntax
    {
        TypeIdSyntax(ifc::File const& ifc, ifc::TypeIdSyntax const& syntax)
            : ifc_(ifc)
            , syntax_(syntax)
        {
        }

        TypeSpecifierSyntax type_specifier() const;

    private:
        ifc::File const & ifc_;
        ifc::TypeIdSyntax const& syntax_;
    };
}
