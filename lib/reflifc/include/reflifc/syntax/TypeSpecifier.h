#pragma once

#include <ifc/FileFwd.h>
#include <ifc/SyntaxTreeFwd.h>

namespace reflifc
{
    struct Syntax;

    struct TypeSpecifierSyntax
    {
        TypeSpecifierSyntax(ifc::File const& ifc, ifc::TypeSpecifierSeq const& syntax)
            : ifc_(ifc)
            , syntax_(syntax)
        {
        }

        Syntax typename_() const;

    private:
        ifc::File const & ifc_;
        ifc::TypeSpecifierSeq const& syntax_;
    };
}
