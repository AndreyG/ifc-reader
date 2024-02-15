module;

#include <compare>

export module reflifc:Attribute;

export import :Word;

import ifc;

namespace reflifc
{
    export struct AttributeCalled;

    export struct Attribute
    {
        Attribute(ifc::File const* ifc, ifc::AttrIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        bool is_basic() const { return index_.sort() == ifc::AttrSort::Basic; }
        Word as_basic() const;

        bool            is_called() const { return index_.sort() == ifc::AttrSort::Called; }
        AttributeCalled as_called() const;

        auto operator<=>(Attribute const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::AttrIndex index_;
    };

    export struct AttributeCalled
    {
        AttributeCalled(ifc::File const* ifc, ifc::AttrCalled const& attr)
            : ifc_(ifc)
            , attr_(&attr)
        {
        }

        Attribute function() const  { return { ifc_, attr_->function }; }
        Attribute arguments() const { return { ifc_, attr_->arguments }; }

        auto operator<=>(AttributeCalled const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::AttrCalled const* attr_;
    };
}
