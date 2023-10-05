module;

#include <compare>

export module reflifc:Pointer;

import :Type;

import ifc;

namespace reflifc
{
    export struct PointerType
    {
        PointerType(ifc::File const* ifc, ifc::PointerType pointer)
            : pointee(ifc, pointer.pointee)
        {
        }

        auto operator<=>(PointerType const& other) const = default;

        Type pointee;
    };
}
