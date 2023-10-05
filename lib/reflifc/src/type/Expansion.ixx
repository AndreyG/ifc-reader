module;

#include <compare>

export module reflifc:ExpansionType;

import :Type;

import ifc;

namespace reflifc
{
    struct Type;

    export struct ExpansionType
    {
        ExpansionType(ifc::File const* ifc, ifc::ExpansionType const& expansion)
            : ifc_(ifc)
            , expansion_(&expansion)
        {
        }

        Type pack() const { return { ifc_, expansion_->pack }; }

        auto operator<=>(ExpansionType const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::ExpansionType const* expansion_;
    };
}
