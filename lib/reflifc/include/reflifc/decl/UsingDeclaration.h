#pragma once

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Declaration;

    struct UsingDeclaration
    {
        UsingDeclaration(ifc::File const* ifc, ifc::UsingDeclaration const& using_decl)
            : ifc_(ifc)
            , using_decl_(&using_decl)
        {
        }

        Declaration resolution() const;
        Declaration home_scope() const;

    private:
        ifc::File const* ifc_;
        ifc::UsingDeclaration const* using_decl_;
    };
}
