module;

#include <compare>

export module reflifc:BaseType;

import :Type;
import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct BaseType
    {
        BaseType(ifc::File const* ifc, ifc::BaseType base)
            : type(ifc, base.type)
            , access(base.access)
            , specifiers(base.specifiers)
        {
        }

        auto operator<=>(BaseType const& other) const = default;

        Type type;
        ifc::Access access;
        ifc::BaseType::Specifiers specifiers;
    };
}

template<>
struct std::hash<reflifc::BaseType>
{
    size_t operator()(reflifc::BaseType object) const noexcept
    {
        return reflifc::hash_combine(0, object.type, static_cast<uint32_t>(object.access), static_cast<uint32_t>(object.specifiers) );
    }
};
