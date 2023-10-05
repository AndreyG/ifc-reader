module;

#include <compare>

export module reflifc:BaseType;

import :Type;

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
