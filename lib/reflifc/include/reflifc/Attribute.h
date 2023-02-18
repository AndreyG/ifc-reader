#pragma once

#include <ifc/FileFwd.h>
#include <ifc/AttributeFwd.h>

namespace reflifc
{
    struct Word;

    struct AttributeCalled;

    struct Attribute
    {
        Attribute(ifc::File const& ifc, ifc::AttrIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        bool is_basic() const;
        Word as_basic() const;

        bool            is_called() const;
        AttributeCalled as_called() const;

    private:
        ifc::File const& ifc_;
        ifc::AttrIndex index_;
    };

    struct AttributeCalled
    {
        AttributeCalled(ifc::File const& ifc, ifc::AttrCalled const& attr)
            : ifc_(ifc)
            , attr_(attr)
        {
        }

        Attribute function() const;
        Attribute arguments() const;

    private:
        ifc::File const& ifc_;
        ifc::AttrCalled const& attr_;
    };
}