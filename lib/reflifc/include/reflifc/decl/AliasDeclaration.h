#pragma once

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Type;
    struct Declaration;

    struct AliasDeclaration
    {
        AliasDeclaration(ifc::File const& ifc, ifc::AliasDeclaration const& alias)
            : ifc_(ifc)
            , alias_(alias)
        {
        }

        char const* name()      const;
        Type        aliasee()   const;
        Declaration home_scope()const;
        ifc::Access access()    const;

    private:
        ifc::File const & ifc_;
        ifc::AliasDeclaration const& alias_;
    };
}
