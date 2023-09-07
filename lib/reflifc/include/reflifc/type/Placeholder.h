#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;

    struct PlaceholderType
    {
        PlaceholderType(ifc::File const* ifc, ifc::PlaceholderType const& placeholder)
            : ifc_(ifc),
              placeholder_(&placeholder)
        {
        }

        ifc::TypeBasis basis() const;
        Type elaboration() const;

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