module;

#include <compare>

export module reflifc:Reference;

import :Type;

import ifc;

export namespace reflifc
{
    struct LvalueReference
    {
        LvalueReference(ifc::File const* ifc, ifc::LvalueReference ref)
            : referee(ifc, ref.referee)
        {
        }

        auto operator<=>(LvalueReference const& other) const = default;

        Type referee;
    };

    struct RvalueReference
    {
        RvalueReference(ifc::File const* ifc, ifc::RvalueReference ref)
            : referee(ifc, ref.referee)
        {
        }

        auto operator<=>(RvalueReference const& other) const = default;

        Type referee;
    };    
}
