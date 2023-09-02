#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/DeclarationFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Name;
    struct Namespace;
    struct ClassOrStruct;
    struct Declaration;

    struct ScopeDeclaration
    {
        ScopeDeclaration(ifc::File const* ifc, ifc::ScopeDeclaration const& scope)
            : ifc_(ifc)
            , scope_(&scope)
        {
        }

        Name name() const;
        Declaration home_scope() const;

        bool        is_namespace() const;
        Namespace   as_namespace() const;

        bool            is_class_or_struct() const;
        ClassOrStruct   as_class_or_struct() const;

        ifc::BasicSpecifiers specifiers() const;
        ifc::TypeBasis kind() const;

        auto operator<=>(ScopeDeclaration const& other) const = default;

    private:
        friend std::hash<ScopeDeclaration>;

        ifc::File const* ifc_;
        ifc::ScopeDeclaration const* scope_;
    };
}

template<>
struct std::hash<reflifc::ScopeDeclaration>
{
    size_t operator()(reflifc::ScopeDeclaration const& scope_decl) const noexcept
    {
        return reflifc::hash_combine(0, scope_decl.ifc_, scope_decl.scope_);
    }
};
