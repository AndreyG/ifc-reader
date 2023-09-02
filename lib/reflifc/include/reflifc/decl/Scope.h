#pragma once

#include "reflifc/Declaration.h"
#include "reflifc/ViewOf.h"
#include "reflifc/HashCombine.h"

#include <ifc/File.h>
#include <ifc/Declaration.h>

namespace reflifc
{
    struct Scope
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

        auto operator<=>(Scope const& other) const = default;
        
    private:
        friend std::hash<Scope>;

        ifc::File const* ifc_;
        ifc::ScopeIndex scope_;
    };
}

template<>
struct std::hash<reflifc::Scope>
{
    size_t operator()(reflifc::Scope const& scope) const noexcept
    {
        return reflifc::hash_combine(0, scope.ifc_, static_cast<uint32_t>(scope.scope_));
    }
};
