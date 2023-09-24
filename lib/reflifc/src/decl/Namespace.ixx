module;

#include <functional>

export module reflifc:Namespace;

import :Name;
import :Scope;

import reflifc.HashCombine;

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
        friend std::hash<Namespace>;

        ifc::File const* ifc_;
        ifc::ScopeDeclaration const* scope_;
    };
}

template<>
struct std::hash<reflifc::Namespace>
{
    size_t operator()(reflifc::Namespace namespace_) const noexcept
    {
        return reflifc::hash_combine(0, namespace_.ifc_, namespace_.scope_);
    }
};
