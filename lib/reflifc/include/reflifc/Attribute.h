#pragma once

#include "HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/AttributeFwd.h>

namespace reflifc
{
    struct Word;

    struct AttributeCalled;

    struct Attribute
    {
        Attribute(ifc::File const* ifc, ifc::AttrIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        bool is_basic() const;
        Word as_basic() const;

        bool            is_called() const;
        AttributeCalled as_called() const;

        auto operator<=>(Attribute const& other) const = default;

    private:
        friend std::hash<Attribute>;

        ifc::File const* ifc_;
        ifc::AttrIndex index_;
    };

    struct AttributeCalled
    {
        AttributeCalled(ifc::File const* ifc, ifc::AttrCalled const& attr)
            : ifc_(ifc)
            , attr_(&attr)
        {
        }

        Attribute function() const;
        Attribute arguments() const;

        auto operator<=>(AttributeCalled const& other) const = default;

    private:
        friend std::hash<AttributeCalled>;

        ifc::File const* ifc_;
        ifc::AttrCalled const* attr_;
    };
}

template<>
struct std::hash<reflifc::Attribute>
{
    size_t operator()(reflifc::Attribute const& attribute) const noexcept
    {
        return reflifc::hash_combine(0, attribute.ifc_, attribute.index_);
    }
};

template<>
struct std::hash<reflifc::AttributeCalled>
{
    size_t operator()(reflifc::AttributeCalled const& attribute_called) const noexcept
    {
        return reflifc::hash_combine(0, attribute_called.ifc_, attribute_called.attr_);
    }
};
