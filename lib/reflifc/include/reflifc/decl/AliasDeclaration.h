#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Type;
    struct Declaration;

    struct AliasDeclaration
    {
        AliasDeclaration(ifc::File const* ifc, ifc::AliasDeclaration const& alias)
            : ifc_(ifc)
            , alias_(&alias)
        {
        }

        char const* name()      const;
        Type        aliasee()   const;
        Declaration home_scope()const;
        ifc::Access access()    const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(AliasDeclaration const& other) const = default;

    private:
        friend std::hash<AliasDeclaration>;

        ifc::File const* ifc_;
        ifc::AliasDeclaration const* alias_;
    };
}

template<>
struct std::hash<reflifc::AliasDeclaration>
{
    size_t operator()(reflifc::AliasDeclaration alias) const noexcept
    {
        return reflifc::hash_combine(0, alias.ifc_, alias.alias_);
    }
};
