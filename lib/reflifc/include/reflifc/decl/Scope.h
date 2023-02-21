#pragma once

#include "reflifc/Declaration.h"
#include "reflifc/ViewOf.h"

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

    private:
        ifc::File const* ifc_;
        ifc::ScopeIndex scope_;
    };
}
