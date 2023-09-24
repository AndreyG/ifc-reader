module;

#include <functional>

export module reflifc:PlaceholderType;

import :Type;

import reflifc.HashCombine;

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
        friend std::hash<PlaceholderType>;

        ifc::File const* ifc_;
        ifc::PlaceholderType const* placeholder_;
    };
}

template<>
struct std::hash<reflifc::PlaceholderType>
{
    size_t operator()(reflifc::PlaceholderType object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.placeholder_);
    }
};