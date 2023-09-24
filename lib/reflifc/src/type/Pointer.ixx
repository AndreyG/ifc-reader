module;

#include <functional>

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

template<>
struct std::hash<reflifc::PointerType>
{
    size_t operator()(reflifc::PointerType object) const noexcept
    {
        return std::hash<reflifc::Type>{}(object.pointee);
    }
};
