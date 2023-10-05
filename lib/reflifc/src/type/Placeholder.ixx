module;

#include <compare>

export module reflifc:PlaceholderType;

import :Type;

import ifc;

namespace reflifc
{
    export struct PlaceholderType
    {
        PlaceholderType(ifc::File const* ifc, ifc::PlaceholderType const& placeholder)
            : ifc_(ifc),
              placeholder_(&placeholder)
        {
        }

        ifc::TypeBasis basis() const { return placeholder_->basis; }
        Type elaboration() const { return { ifc_, placeholder_->elaboration }; }

        auto operator<=>(PlaceholderType const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::PlaceholderType const* placeholder_;
    };
}
