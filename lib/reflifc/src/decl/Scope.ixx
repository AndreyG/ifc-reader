module;

#include <compare>
#include <ranges>

export module reflifc:Scope;

import :Declaration;
import reflifc.ViewOf;

import ifc;
import ifc.Scope;

namespace reflifc
{
    export struct Scope
    {
        Scope(ifc::File const* ifc, ifc::ScopeIndex scope)
            : ifc_(ifc)
            , scope_(scope)
        {
        }

        ViewOf<Declaration> auto get_declarations() const
        {
            const auto scope_members = ifc_->scope_descriptors()[scope_];
            return ifc::get_declarations(*ifc_, scope_members)
                | std::views::transform([ifc = ifc_] (ifc::Declaration decl) { return Declaration(ifc, decl.index); });
        }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Scope const& other) const = default;
        
    private:
        ifc::File const* ifc_;
        ifc::ScopeIndex scope_;
    };
}
