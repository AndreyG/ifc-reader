module reflifc;

import :Name;

namespace reflifc
{
    bool ClassOrStruct::is_complete() const
    {
        return !is_null(scope_->initializer);
    }

    Name ClassOrStruct::name() const
    {
        return { ifc_, scope_->name };
    }

    ifc::TypeBasis ClassOrStruct::kind() const
    {
        return ifc_->fundamental_types()[scope_->type].basis;
    }

    Declaration ClassOrStruct::home_scope() const
    {
        return { ifc_, scope_->home_scope };
    }
}
