#pragma once

#include "reflifc/HashCombine.h"

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
        ifc::Access access() const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(UsingDeclaration const& other) const = default;

    private:
        friend std::hash<UsingDeclaration>;

        ifc::File const* ifc_;
        ifc::UsingDeclaration const* using_decl_;
    };
}

template<>
struct std::hash<reflifc::UsingDeclaration>
{
    size_t operator()(reflifc::UsingDeclaration using_decl) const noexcept
    {
        return reflifc::hash_combine(0, using_decl.ifc_, using_decl.using_decl_);
    }
};
