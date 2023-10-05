module;

#include <compare>

export module reflifc:ForallType;

import :Chart;
import :Type;

import ifc;

namespace reflifc
{
    struct Chart;
    struct Type;

    export struct ForallType
    {
        ForallType(ifc::File const* ifc, ifc::ForallType const& forall)
            : ifc_(ifc)
            , forall_(&forall)
        {
        }

        Chart   chart()     const { return { ifc_, forall_->chart }; }
        Type    subject()   const { return { ifc_, forall_->subject }; }

        auto operator<=>(ForallType const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::ForallType const* forall_;
    };
}
