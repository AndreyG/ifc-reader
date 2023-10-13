#include "reflifc/decl/UsingDeclaration.h"

#include "reflifc/Declaration.h"

#include <ifc/Declaration.h>

namespace reflifc
{
    Declaration UsingDeclaration::resolution() const
    {
        return { ifc_, using_decl_->resolution };
    }

    Declaration UsingDeclaration::home_scope() const
    {
        return { ifc_, using_decl_->home_scope };
    }

    ifc::Access UsingDeclaration::access() const
    {
        return using_decl_->access;
    }
}
