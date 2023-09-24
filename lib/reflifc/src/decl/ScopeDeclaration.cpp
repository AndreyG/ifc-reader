module;

#include <cassert>

module reflifc;

namespace reflifc
{
    Name ScopeDeclaration::name() const
    {
        return { ifc_, scope_->name };
    }

    Declaration ScopeDeclaration::home_scope() const
    {
        return { ifc_, scope_->home_scope };
    }

    bool ScopeDeclaration::is_namespace() const
    {
        return kind() == ifc::TypeBasis::Namespace;
    }

    Namespace ScopeDeclaration::as_namespace() const
    {
        return { ifc_, *scope_ };
    }

    bool ScopeDeclaration::is_class_or_struct() const
    {
        const auto k = kind();
        return k == ifc::TypeBasis::Class || k == ifc::TypeBasis::Struct;
    }

    ClassOrStruct ScopeDeclaration::as_class_or_struct() const
    {
        assert(is_class_or_struct());
        return { ifc_, *scope_ };
    }

    ifc::BasicSpecifiers ScopeDeclaration::specifiers() const
    {
        return scope_->specifiers;
    }

    ifc::TypeBasis ScopeDeclaration::kind() const
    {
        return get_kind(*scope_, *ifc_);
    }
}
