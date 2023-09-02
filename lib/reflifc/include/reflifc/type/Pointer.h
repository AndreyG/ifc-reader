#pragma once

#include "reflifc/Type.h"

#include <ifc/Type.h>

#include <functional>

namespace reflifc
{
    struct PointerType
    {
        PointerType(ifc::File const* ifc, ifc::PointerType pointer)
            : pointee(ifc, pointer.pointee)
        {
        }

        auto operator<=>(PointerType const& other) const = default;

        Type pointee;
    };
}

template<>
struct std::hash<reflifc::PointerType>
{
    size_t operator()(reflifc::PointerType const& object) const noexcept
    {
        return std::hash<reflifc::Type>{}(object.pointee);
    }
};
