#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;
    struct Expression;

    struct ArrayType
    {
        ArrayType(ifc::File const* ifc, ifc::ArrayType const& array)
            : ifc_(ifc)
            , array_(&array)
        {
        }

        Type        element() const;
        Expression  extent() const;

        auto operator<=>(ArrayType const& other) const = default;

    private:
        friend std::hash<ArrayType>;

        ifc::File const* ifc_;
        ifc::ArrayType const* array_;
    };

    std::uint32_t extent_value(ArrayType);
}

template<>
struct std::hash<reflifc::ArrayType>
{
    size_t operator()(reflifc::ArrayType object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.array_);
    }
};
