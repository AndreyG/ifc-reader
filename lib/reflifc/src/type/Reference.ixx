module;

#include <functional>

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

template<>
struct std::hash<reflifc::LvalueReference>
{
    size_t operator()(reflifc::LvalueReference object) const noexcept
    {
        return std::hash<reflifc::Type>{}(object.referee);
    }
};

template<>
struct std::hash<reflifc::RvalueReference>
{
    size_t operator()(reflifc::RvalueReference object) const noexcept
    {
        return std::hash<reflifc::Type>{}(object.referee);
    }
};
