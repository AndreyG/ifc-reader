#include "reflifc/decl/AliasDeclaration.h"

#include "reflifc/Declaration.h"
#include "reflifc/Type.h"

#include <ifc/Declaration.h>
#include <ifc/File.h>

namespace reflifc
{
    char const* AliasDeclaration::name() const
    {
        return ifc_->get_string(alias_->name);
    }

    Type AliasDeclaration::aliasee() const
    {
        return { ifc_, alias_->aliasee };
    }

    Declaration AliasDeclaration::home_scope() const
    {
        return { ifc_, alias_->home_scope };
    }

    ifc::Access AliasDeclaration::access() const
    {
        return alias_->access;
    }
}
