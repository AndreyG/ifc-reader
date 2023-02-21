#pragma once

#include "decl/Scope.h"
#include "decl/ScopeDeclaration.h"

namespace reflifc
{
    struct UnitDescription
    {
        UnitDescription(ifc::File const* ifc, ifc::UnitIndex unit)
            : unit_(unit)
            , ifc_(ifc)
        {
        }

        bool is_primary() const { return unit_.sort() == ifc::UnitSort::Primary; }

        const char* name() const { return ifc_->get_string(ifc::TextOffset{unit_.index}); }

    private:
        ifc::UnitIndex unit_;
        ifc::File const* ifc_;
    };

    struct Module
    {
        explicit Module(ifc::File const* ifc)
            : ifc_(ifc)
        {
        }

        ViewOf<ScopeDeclaration> auto scope_declarations() const
        {
            return ifc_->scope_declarations()
                | std::views::transform([ifc = ifc_] (ifc::ScopeDeclaration const & scope) {
                    return ScopeDeclaration(ifc, scope);
                });
        }

        Scope global_namespace() const
        {
            return { ifc_, ifc_->header().global_scope };
        }

        UnitDescription unit() const
        {
            return { ifc_, ifc_->header().unit };
        }

    private:
        ifc::File const* ifc_;
    };
}
