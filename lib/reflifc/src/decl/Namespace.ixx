module;

#include <compare>

export module reflifc:Namespace;

import :Name;
import :Scope;

import ifc;

namespace reflifc
{
    export struct Namespace
    {
        Namespace(ifc::File const* ifc, ifc::ScopeDeclaration const& scope)
            : ifc_(ifc)
            , scope_(&scope)
        {
        }

        Name  name()  const { return { ifc_, scope_->name }; }
        Scope scope() const { return { ifc_, scope_->initializer }; }

        bool is_inline() const { return ifc::is_inline(*scope_); }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Namespace const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::ScopeDeclaration const* scope_;
    };
}
